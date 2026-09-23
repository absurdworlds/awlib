#!/usr/bin/env python3
"""
Turn clang-tidy output from a build log into a SARIF file and a Markdown
summary. Warnings in headers are reported once per translation unit that
includes them, so they are deduplicated by location and check.
"""
import argparse
import collections
import json
import os
import re
import sys

DIAG = re.compile(r'^(.+?):(\d+):(\d+): (warning|error): (.*) \[([^\]]+)\]$')


def canonical(names):
	"""
	Aliases are listed together in no fixed order, e.g.
	[cert-err58-cpp,bugprone-throwing-static-initialization] or
	[misc-static-assert,cert-dcl03-c]. cert-* checks are mostly aliases
	of the others, so prefer anything else. The compiler's own warnings
	end up in the same log as [-Wswitch]; clang-tidy reports the same
	thing as [clang-diagnostic-switch].
	"""
	names = ['clang-diagnostic-' + n[2:] if n.startswith('-W') else n for n in names]
	return min(names, key=lambda n: (n.startswith('cert-'), n))


def parse(log, root):
	found = {}
	outside = 0
	for line in log:
		m = DIAG.match(line.rstrip('\n'))
		if not m:
			continue
		path, row, col, level, msg, checks = m.groups()
		path = os.path.normpath(path)
		if os.path.isabs(path):
			path = os.path.relpath(path, root)
		if path.startswith('..'):
			outside += 1
			continue
		key = (path, int(row), int(col), canonical(checks.split(',')))
		found.setdefault(key, (level, msg))
	return found, outside


def help_uri(check):
	if check.startswith('clang-diagnostic-'):
		return None
	if check.startswith('clang-analyzer-'):
		group, name = 'clang-analyzer', check[len('clang-analyzer-'):]
	else:
		group, name = check.split('-', 1)
	return f'https://clang.llvm.org/extra/clang-tidy/checks/{group}/{name}.html'


def sarif(found):
	checks = sorted({key[3] for key in found})
	rules = []
	for check in checks:
		rule = {'id': check}
		uri = help_uri(check)
		if uri:
			rule['helpUri'] = uri
		rules.append(rule)

	results = []
	for (path, row, col, check), (level, msg) in sorted(found.items()):
		results.append({
			'ruleId': check,
			'level': level,
			'message': {'text': msg},
			'locations': [{
				'physicalLocation': {
					'artifactLocation': {'uri': path, 'uriBaseId': '%SRCROOT%'},
					'region': {'startLine': row, 'startColumn': col},
				},
			}],
		})

	return {
		'$schema': 'https://json.schemastore.org/sarif-2.1.0.json',
		'version': '2.1.0',
		'runs': [{
			'tool': {'driver': {'name': 'clang-tidy', 'rules': rules}},
			'results': results,
		}],
	}


def table(title, counts):
	out = [f'| {title} | count |', '|---|---:|']
	for name, n in counts.most_common():
		out.append(f'| `{name}` | {n} |')
	return '\n'.join(out)


def summary(found, outside):
	by_check = collections.Counter(key[3] for key in found)
	by_dir   = collections.Counter(key[0].split(os.sep)[0] for key in found)
	errors   = sum(1 for level, _ in found.values() if level == 'error')

	out = ['## clang-tidy', '']
	out.append(f'**{len(found)}** unique diagnostics ({errors} errors)'
	           f' across {len(by_check)} checks.')
	if outside:
		out.append(f'{outside} diagnostics outside the source tree were skipped.')
	out += ['', table('check', by_check), '', table('directory', by_dir), '']
	return '\n'.join(out)


def main():
	ap = argparse.ArgumentParser(description=__doc__)
	ap.add_argument('log', help='build log containing clang-tidy output')
	ap.add_argument('--root', default='.', help='source root; paths in the SARIF are relative to it')
	ap.add_argument('--sarif', help='write SARIF here')
	ap.add_argument('--summary', default=os.environ.get('GITHUB_STEP_SUMMARY'),
	                help='append Markdown here (default: $GITHUB_STEP_SUMMARY, else stdout)')
	args = ap.parse_args()

	with open(args.log, encoding='utf-8', errors='replace') as log:
		found, outside = parse(log, os.path.abspath(args.root))

	if args.sarif:
		with open(args.sarif, 'w', encoding='utf-8') as f:
			json.dump(sarif(found), f, indent=1)

	text = summary(found, outside)
	if args.summary:
		with open(args.summary, 'a', encoding='utf-8') as f:
			f.write(text + '\n')
	else:
		sys.stdout.write(text + '\n')


if __name__ == '__main__':
	main()
