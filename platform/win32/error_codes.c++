#include <system_error>
#include <windows.h>
namespace aw {
namespace win32 {
// based on https://stackoverflow.com/questions/3952342/
// (mingw32 and cygwin sources)
// TODO: look at tclWinError.c
#define WINAPI_ERROR_MAP\
	X(invalid_argument,               EINVAL,       INVALID_FUNCTION );/*ENOSYS?*/\
	X(no_such_file_or_directory,      ENOENT,       FILE_NOT_FOUND );\
	X(no_such_file_or_directory,      ENOENT,       PATH_NOT_FOUND );\
	X(too_many_files_open,            EMFILE,       TOO_MANY_OPEN_FILES, 4 );\
	X(permission_denied,              EACCES,       ACCESS_DENIED );\
	X(bad_file_descriptor,            EBADF,        INVALID_HANDLE );\
	X(not_enough_memory,              ENOMEM,       ARENA_TRASHED );\
	X(not_enough_memory,              ENOMEM,       NOT_ENOUGH_MEMORY, 8 );\
	X(not_enough_memory,              ENOMEM,       INVALID_BLOCK );/*EFAULT?*/\
	X(argument_list_too_long,         E2BIG,        BAD_ENVIRONMENT );\
	X(executable_format_error,        ENOEXEC,      BAD_FORMAT, 11 );\
	X(invalid_argument,               EINVAL,       INVALID_ACCESS, 12 );/*EACCESS?*/\
	X(invalid_argument,               EINVAL,       INVALID_DATA );\
	X(not_enough_memory,              ENOMEM,       OUTOFMEMORY, 14 );\
	X(no_such_file_or_directory,      ENOENT,       INVALID_DRIVE );/*ENODEV?*/\
	X(permission_denied,              EACCES,       CURRENT_DIRECTORY );\
	X(cross_device_link,              EXDEV,        NOT_SAME_DEVICE, 17 );\
	X(no_such_file_or_directory,      ENOENT,       NO_MORE_FILES );\
	X(read_only_file_system,          EROFS,        WRITE_PROTECT );\
	X(no_such_device,                 ENODEV,       BAD_UNIT );\
	X(permission_denied,              EACCES,       NOT_READY, 21 );/*EAGAIN?*/\
	X(io_error,                       EIO,          BAD_COMMAND );\
	X(io_error,                       EIO,          CRC );\
	X(io_error,                       EIO,          BAD_LENGTH );\
	X(permission_denied,              EACCES,       SEEK );/*EIO?*/\
	X(permission_denied,              EACCES,       NOT_DOS_DISK );\
	X(io_error,                       EIO,          SECTOR_NOT_FOUND );\
	X(io_error,                       EIO,          OUT_OF_PAPER, 28 );/*EBUSY?*/\
	X(io_error,                       EIO,          WRITE_FAULT, 29 );\
	X(io_error,                       EIO,          READ_FAULT, 30 );\
	X(io_error,                       EIO,          GEN_FAILURE, 31 );\
	X(permission_denied,              EACCES,       SHARING_VIOLATION, 32 );\
	X(permission_denied,              EACCES,       LOCK_VIOLATION, 33 );\
	X(permission_denied,              EACCES,       WRONG_DISK, 34 );\
	X(too_many_files_open_in_system,  ENFILE,       SHARING_BUFFER_EXCEEDED, 36 );\
	X(no_space_on_device,             ENOSPC,       HANDLE_DISK_FULL, 39 );\
	X(function_not_supported,         ENOSYS,       NOT_SUPPORTED, 50 );\
	X(device_or_resource_busy,        EBUSY,        REM_NOT_LIST, 51 );\
	X(file_exists,                    EEXIST,       DUP_NAME, 52 );\
	X(no_such_file_or_directory,      ENOENT,       BAD_NETPATH );\
	X(device_or_resource_busy,        EBUSY,        NETWORK_BUSY );\
	X(no_such_device,                 ENODEV,       DEV_NOT_EXIST, 55 );\
	X(resource_unavailable_try_again, EAGAIN,       TOO_MANY_CMDS );\
	X(invalid_argument,               EINVAL,       ADAP_HDW_ERR );\
	X(io_error,                       EIO,          BAD_NET_RESP );\
	X(io_error,                       EIO,          UNEXP_NET_ERR );\
	X(file_too_large,                 EFBIG,        PRINTQ_FULL, 61 );\
	X(no_space_on_device,             ENOSPC,       NO_SPOOL_SPACE, 62 );\
	X(invalid_argument,               EINVAL,       PRINT_CANCELLED );\
	X(invalid_argument,               EINVAL,       NETNAME_DELETED );\
	X(permission_denied,              EACCES,       NETWORK_ACCESS_DENIED );\
	X(invalid_argument,               EINVAL,       BAD_DEV_TYPE );\
	X(no_such_file_or_directory,      ENOENT,       BAD_NET_NAME );\
	X(too_many_files_open_in_system,  ENFILE,       TOO_MANY_NAMES, 68 );\
	X(io_error,                       EIO,          TOO_MANY_SESS, 69 );\
	X(resource_unavailable_try_again, EAGAIN,       SHARING_PAUSED, 70 );\
	X(invalid_argument,               EINVAL,       REQ_NOT_ACCEP );\
	X(invalid_argument,               EINVAL,       REDIR_PAUSED );\
	X(file_exists,                    EEXIST,       FILE_EXISTS );\
	X(operation_not_permitted,        EPERM,        CANNOT_MAKE, 82 );\
	X(permission_denied,              EACCES,       FAIL_I24, 83 );\
	X(invalid_argument,               EINVAL,       OUT_OF_STRUCTURES );\
	X(device_or_resource_busy,        EBUSY,        ALREADY_ASSIGNED, 85 );\
	X(operation_not_permitted,        EPERM,        INVALID_PASSWORD, 86 );/*EINVAL?*/\
	X(invalid_argument,               EINVAL,       INVALID_PARAMETER, 87 );\
	X(io_error,                       EIO,          NET_WRITE_FAULT );\
	X(resource_unavailable_try_again, EAGAIN,       NO_PROC_SLOTS );\
	X(invalid_argument,               EINVAL,       TOO_MANY_SEMAPHORES );\
	X(invalid_argument,               EINVAL,       EXCL_SEM_ALREADY_OWNED );\
	X(invalid_argument,               EINVAL,       SEM_IS_SET );\
	X(invalid_argument,               EINVAL,       TOO_MANY_SEM_REQUESTS );\
	X(invalid_argument,               EINVAL,       INVALID_AT_INTERRUPT_TIME );\
	X(io_error,                       EIO,          DISK_CHANGE );\
	X(permission_denied,              EACCES,       DRIVE_LOCKED );\
	X(broken_pipe,                    EPIPE,        BROKEN_PIPE, 109 );\
	X(io_error,                       EIO,          OPEN_FAILED, 110 );\
	X(filename_too_long,              ENAMETOOLONG, BUFFER_OVERFLOW, 111 );\
	X(no_space_on_device,             ENOSPC,       DISK_FULL );\
	X(too_many_files_open_in_system,  ENFILE,       NO_MORE_SEARCH_HANDLES ); /*EIO?*/\
	X(bad_file_descriptor,            EBADF,        INVALID_TARGET_HANDLE, 114 );/*EIO?*/\
	X(invalid_argument,               EINVAL,       INVALID_CATEGORY );\
	X(invalid_argument,               EINVAL,       INVALID_VERIFY_SWITCH );\
	X(no_such_device_or_address,      ENXIO,        BAD_DRIVER_LEVEL, 119 );\
	X(function_not_supported,         ENOSYS,       CALL_NOT_IMPLEMENTED, 120 );\
	X(invalid_argument,               EINVAL,       SEM_TIMEOUT );\
	X(not_enough_memory,              ENOMEM,       INSUFFICIENT_BUFFER );\
	X(invalid_argument,               EINVAL,       INVALID_NAME, 123 );/*ENOENT?*/\
	X(invalid_argument,               EINVAL,       INVALID_LEVEL );\
	X(invalid_argument,               EINVAL,       NO_VOLUME_LABEL );\
	X(no_such_file_or_directory,      ENOENT,       MOD_NOT_FOUND );\
	X(no_such_process,                ESRCH,        PROC_NOT_FOUND, 127 );\
	X(no_child_process,               ECHILD,       WAIT_NO_CHILDREN, 128 );\
	X(resource_unavailable_try_again, EAGAIN,       CHILD_NOT_COMPLETE, 129 );/*ECHILD?*/\
	X(bad_file_descriptor,            EBADF,        DIRECT_ACCESS_HANDLE, 130 );\
	X(invalid_seek,                   ESPIPE,       NEGATIVE_SEEK, 131);\
	X(permission_denied,              EACCES,       SEEK_ON_DEVICE, 132 ); /* ESPIPE? */\
	X(device_or_resource_busy,        EBUSY,        BUSY_DRIVE, 142 );/*EAGAIN?*/\
	X(invalid_argument,               EINVAL,       SAME_DRIVE );\
	X(invalid_argument,               EINVAL,       DIR_NOT_ROOT );\
	X(directory_not_empty,            ENOTEMPTY,    DIR_NOT_EMPTY, 145 );\
	X(device_or_resource_busy,        EBUSY,        PATH_BUSY, 148 );\
	X(invalid_argument,               EINVAL,       IS_SUBST_TARGET );\
	X(invalid_argument,               EINVAL,       INVALID_EVENT_COUNT );\
	X(invalid_argument,               EINVAL,       INVALID_LIST_FORMAT );\
	X(invalid_argument,               EINVAL,       LABEL_TOO_LONG );\
	X(invalid_argument,               EINVAL,       TOO_MANY_TCBS );\
	X(io_error,                       EIO,          SIGNAL_REFUSED );\
	X(invalid_argument,               EINVAL,       DISCARDED );\
	X(permission_denied,              EACCES,       NOT_LOCKED, 158 );\
	X(invalid_argument,               EINVAL,       BAD_THREADID_ADDR );\
	X(invalid_argument,               EINVAL,       BAD_ARGUMENTS );\
	X(no_such_file_or_directory,      ENOENT,       BAD_PATHNAME, 161 );\
	X(device_or_resource_busy,        EBUSY,        SIGNAL_PENDING );\
	X(resource_unavailable_try_again, EAGAIN,       MAX_THRDS_REACHED );\
	X(permission_denied,              EACCES,       LOCK_FAILED, 167 );\
	X(device_or_resource_busy,        EBUSY,        BUSY );\
	X(invalid_argument,               EINVAL,       CANCEL_VIOLATION );\
	X(invalid_argument,               EINVAL,       ATOMIC_LOCKS_NOT_SUPPORTED, 174 );/*ENOSYS?*/\
	X(executable_format_error,        ENOEXEC,      INVALID_SEGMENT_NUMBER );\
	X(executable_format_error,        ENOEXEC,      INVALID_ORDINAL );\
	X(file_exists,                    EEXIST,       ALREADY_EXISTS, 183 );\
	X(invalid_argument,               EINVAL,       INVALID_FLAG_NUMBER );\
	X(invalid_argument,               EINVAL,       SEM_NOT_FOUND );\
	X(executable_format_error,        ENOEXEC,      INVALID_STARTING_CODESEG );\
	X(executable_format_error,        ENOEXEC,      INVALID_STACKSEG );\
	X(executable_format_error,        ENOEXEC,      INVALID_MODULETYPE );\
	X(executable_format_error,        ENOEXEC,      INVALID_EXE_SIGNATURE );\
	X(executable_format_error,        ENOEXEC,      EXE_MARKED_INVALID );\
	X(executable_format_error,        ENOEXEC,      BAD_EXE_FORMAT, 193 );\
	X(executable_format_error,        ENOEXEC,      ITERATED_DATA_EXCEEDS_64k );\
	X(executable_format_error,        ENOEXEC,      INVALID_MINALLOCSIZE );\
	X(executable_format_error,        ENOEXEC,      DYNLINK_FROM_INVALID_RING );\
	X(executable_format_error,        ENOEXEC,      IOPL_NOT_ENABLED );\
	X(executable_format_error,        ENOEXEC,      INVALID_SEGDPL );\
	X(executable_format_error,        ENOEXEC,      AUTODATASEG_EXCEEDS_64k );\
	X(executable_format_error,        ENOEXEC,      RING2SEG_MUST_BE_MOVABLE );\
	X(executable_format_error,        ENOEXEC,      RELOC_CHAIN_XEEDS_SEGLIM );\
	X(executable_format_error,        ENOEXEC,      INFLOOP_IN_RELOC_CHAIN );\
	X(invalid_argument,               EINVAL,       ENVVAR_NOT_FOUND );\
	X(io_error,                       EIO,          NO_SIGNAL_SENT, 205 );\
	X(filename_too_long,              ENAMETOOLONG, FILENAME_EXCED_RANGE, 206 );\
	X(argument_list_too_long,         E2BIG,        META_EXPANSION_TOO_LONG, 208 );\
	X(invalid_argument,               EINVAL,       INVALID_SIGNAL_NUMBER, 209 );\
	X(device_or_resource_busy,        EBUSY,        LOCKED, 212);\
	X(too_many_files_open,            EMFILE,       TOO_MANY_MODULES, 214);\
	X(resource_unavailable_try_again, EAGAIN,       NESTING_NOT_ALLOWED, 215);\
	X(executable_format_error,        ENOEXEC,      EXE_MACHINE_TYPE_MISMATCH, 216 );\
	X(broken_pipe,                    EPIPE,        BAD_PIPE, 230 );\
	X(resource_unavailable_try_again, EAGAIN,       PIPE_BUSY, 231);\
	X(broken_pipe,                    EPIPE,        NO_DATA, 232);\
	X(broken_pipe,                    EPIPE,        PIPE_NOT_CONNECTED, 233 );\
	X(message_size,                   EMSGSIZE,     MORE_DATA, 234 );/*EAGAIN?EPIPE?*/\
	X(invalid_argument,               EINVAL,       INVALID_EA_NAME,   245);\
	X(invalid_argument,               EINVAL,       EA_LIST_INCONSISTENT,  255);\
	X(invalid_argument,               EINVAL,       DIRECTORY, 267);\
	X(no_space_on_device,             ENOSPC,       EAS_DIDNT_FIT, 275 );\
	X(no_space_on_device,             ENOSPC,       EA_TABLE_FULL, 277 );\
	X(function_not_supported,         ENOSYS,       EAS_NOT_SUPPORTED, 282 );\
	X(bad_address,                    EFAULT,       INVALID_ADDRESS, 487);\
	X(result_out_of_range,            ERANGE,       ARITHMETIC_OVERFLOW, 534);\
	X(resource_unavailable_try_again, EAGAIN,       PIPE_CONNECTED, 535);/*EPIPE?*/\
	X(resource_unavailable_try_again, EAGAIN,       PIPE_LISTENING, 536);/*EPIPE?*/\
	X(interrupted,                    EINTR,        OPERATION_ABORTED, 995);\
	X(resource_unavailable_try_again, EAGAIN,       IO_INCOMPLETE, 996);/*EINTR?*/\
	X(resource_unavailable_try_again, EAGAIN,       IO_PENDING, 997);\
	X(bad_address,                    EFAULT,       NOACCESS, 998);\
	X(no_such_file_or_directory,      ENOENT,       SWAPERROR, 999);\
	X(not_enough_memory,              ENOMEM,       STACK_OVERFLOW, 1001);\
	X(invalid_argument,               EINVAL,       INVALID_FLAGS, 1004);\
	X(no_such_device,                 ENODEV,       UNRECOGNIZED_VOLUME, 1005);\
	X(no_such_device_or_address,      ENXIO,        FILE_INVALID, 1006);\
	X(io_error,                       EIO,          CANTOPEN, 1011);\
	X(io_error,                       EIO,          CANTREAD, 1012);\
	X(io_error,                       EIO,          CANTWRITE, 1013);\
	X(device_or_resource_busy,        EBUSY,        SERVICE_REQUEST_TIMEOUT, 1053);\
	X(bad_address,                    EFAULT,       PROCESS_ABORTED, 1067);\
	X(no_space_on_device,             ENOSPC,       END_OF_MEDIA, 1100 );\
	X(io_error,                       EIO,          FILEMARK_DETECTED, 1101);\
	X(io_error,                       EIO,          BEGINNING_OF_MEDIA, 1102);\
	X(io_error,                       EIO,          SETMARK_DETECTED, 1103);\
	X(io_error,                       EIO,          NO_DATA_DETECTED, 1104);\
	X(io_error,                       EIO,          INVALID_BLOCK_LENGTH, 1106);\
	X(io_error,                       EIO,          BUS_RESET, 1111);\
	X(io_error,                       EIO,          IO_DEVICE, 1117);\
	X(io_error,                       EIO,          EOM_OVERFLOW, 1129);\
	X(resource_deadlock_would_occur,  EDEADLK,      POSSIBLE_DEADLOCK, 1131);\
	X(invalid_argument,               EINVAL,       MAPPED_ALIGNMENT, 1132);\
	X(too_many_links,                 EMLINK,       TOO_MANY_LINKS, 1142);\
	X(io_error,                       EIO,          DEVICE_REQUIRES_CLEANING, 1165);\
	X(io_error,                       EIO,          DEVICE_DOOR_OPEN, 1166);\
	X(no_such_device,                 ENODEV,       BAD_DEVICE, 1200);\
	X(interrupted,                    EINTR,        CANCELLED, 1223);\
	X(connection_refused,             ECONNREFUSED, CONNECTION_REFUSED, 1225);\
	X(invalid_argument,               EINVAL,       INVALID_OWNER, 1307);\
	X(invalid_argument,               EINVAL,       INVALID_PRIMARY_GROUP, 1308);\
	X(permission_denied,              EACCES,       PRIVILEGE_NOT_HELD, 1314 );\
	X(permission_denied,              EACCES,       LOGON_FAILURE, 1326 );\
	X(permission_denied,              EACCES,       ACCOUNT_RESTRICTION, 1327 );\
	X(permission_denied,              EACCES,       INVALID_LOGON_HOURS, 1328 );\
	X(permission_denied,              EACCES,       INVALID_WORKSTATION, 1329 );\
	X(permission_denied,              EACCES,       PASSWORD_EXPIRED, 1330 );\
	X(permission_denied,              EACCES,       ACCOUNT_DISABLED, 1331 );\
	X(invalid_argument,               EINVAL,       NONE_MAPPED, 1332);\
	X(io_error,                       EIO,          DISK_CORRUPT, 1393);\
	X(file_too_large,                 EFBIG,        NO_SYSTEM_RESOURCES, 1450);\
	X(resource_unavailable_try_again, EAGAIN,       NONPAGED_SYSTEM_RESOURCES, 1451);\
	X(resource_unavailable_try_again, EAGAIN,       PAGED_SYSTEM_RESOURCES, 1452);\
	X(resource_unavailable_try_again, EAGAIN,       WORKING_SET_QUOTA, 1453);\
	X(resource_unavailable_try_again, EAGAIN,       PAGEFILE_QUOTA, 1454);\
	X(device_or_resource_busy,        EBUSY,        TIMEOUT, 1460);\
	X(no_such_device_or_address,      ENXIO,        UNRECOGNIZED_MEDIA, 1785);\
	X(not_enough_memory,              ENOMEM,       NOT_ENOUGH_QUOTA, 1816);\
	X(invalid_argument,               EINVAL,       BAD_USERNAME, 2202);\
	X(not_connected,                  ENOTCONN,     NOT_CONNECTED, 2250);\
	X(resource_unavailable_try_again, EAGAIN,       OPEN_FILES, 2401);/*EBUSY?*/\
	X(resource_unavailable_try_again, EAGAIN,       ACTIVE_CONNECTIONS, 2402);\
	X(resource_unavailable_try_again, EAGAIN,       DEVICE_IN_USE, 2404);\
	X(io_error,                       EIO,          DS_GENERIC_ERROR, 8341);


std::errc map_error_code(int code)
{
	auto winapi_code = static_cast<DWORD>(code);
	switch (winapi_code) {
#define X( code, posix, winapi, ... ) case ERROR_##winapi: return std::errc::code
		WINAPI_ERROR_MAP
#undef X
	default: return std::errc::invalid_argument;
	}
}
} // namespace win32
} // namespace aw
