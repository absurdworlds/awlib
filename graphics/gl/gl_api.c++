#include <aw/gl/api/gl_46.h>
#include <aw/gl/loader.h>

#include <vector>
#include <aw/types/string_view.h>
#include <aw/algorithm/binary_find.h>

namespace gl {
using aw::string_view;
using namespace aw::gl;

namespace ext {
} //namespace ext

#define aw_gl_func_pointer(x) decltype(x) x = nullptr
/* gl version 1.0 */
aw_gl_func_pointer(blend_func);
aw_gl_func_pointer(clear);
aw_gl_func_pointer(clear_color);
aw_gl_func_pointer(clear_depth);
aw_gl_func_pointer(clear_stencil);
aw_gl_func_pointer(color_mask);
aw_gl_func_pointer(cull_face);
aw_gl_func_pointer(depth_func);
aw_gl_func_pointer(depth_mask);
aw_gl_func_pointer(depth_range);
aw_gl_func_pointer(disable);
aw_gl_func_pointer(draw_buffer);
aw_gl_func_pointer(enable);
aw_gl_func_pointer(finish);
aw_gl_func_pointer(flush);
aw_gl_func_pointer(front_face);
aw_gl_func_pointer(get_boolean_v);
aw_gl_func_pointer(get_double_v);
aw_gl_func_pointer(get_error);
aw_gl_func_pointer(get_float_v);
aw_gl_func_pointer(get_integer_v);
aw_gl_func_pointer(get_string);
aw_gl_func_pointer(get_tex_image);
aw_gl_func_pointer(get_tex_level_parameter_fv);
aw_gl_func_pointer(get_tex_level_parameter_iv);
aw_gl_func_pointer(get_tex_parameter_fv);
aw_gl_func_pointer(get_tex_parameter_iv);
aw_gl_func_pointer(hint);
aw_gl_func_pointer(is_enabled);
aw_gl_func_pointer(line_width);
aw_gl_func_pointer(logic_op);
aw_gl_func_pointer(pixel_store_f);
aw_gl_func_pointer(pixel_store_i);
aw_gl_func_pointer(point_size);
aw_gl_func_pointer(polygon_mode);
aw_gl_func_pointer(read_buffer);
aw_gl_func_pointer(read_pixels);
aw_gl_func_pointer(scissor);
aw_gl_func_pointer(stencil_func);
aw_gl_func_pointer(stencil_mask);
aw_gl_func_pointer(stencil_op);
aw_gl_func_pointer(tex_image_1d);
aw_gl_func_pointer(tex_image_2d);
aw_gl_func_pointer(tex_parameter_f);
aw_gl_func_pointer(tex_parameter_fv);
aw_gl_func_pointer(tex_parameter_i);
aw_gl_func_pointer(tex_parameter_iv);
aw_gl_func_pointer(viewport);

/* gl version 1.1 */
aw_gl_func_pointer(bind_texture);
aw_gl_func_pointer(copy_tex_image_1d);
aw_gl_func_pointer(copy_tex_image_2d);
aw_gl_func_pointer(copy_tex_sub_image_1d);
aw_gl_func_pointer(copy_tex_sub_image_2d);
aw_gl_func_pointer(delete_textures);
aw_gl_func_pointer(draw_arrays);
aw_gl_func_pointer(draw_elements);
aw_gl_func_pointer(gen_textures);
aw_gl_func_pointer(get_pointer_v);
aw_gl_func_pointer(is_texture);
aw_gl_func_pointer(polygon_offset);
aw_gl_func_pointer(tex_sub_image_1d);
aw_gl_func_pointer(tex_sub_image_2d);

/* gl version 1.2 */
aw_gl_func_pointer(copy_tex_sub_image_3d);
aw_gl_func_pointer(draw_range_elements);
aw_gl_func_pointer(tex_image_3d);
aw_gl_func_pointer(tex_sub_image_3d);

/* gl version 1.3 */
aw_gl_func_pointer(active_texture);
aw_gl_func_pointer(compressed_tex_image_1d);
aw_gl_func_pointer(compressed_tex_image_2d);
aw_gl_func_pointer(compressed_tex_image_3d);
aw_gl_func_pointer(compressed_tex_sub_image_1d);
aw_gl_func_pointer(compressed_tex_sub_image_2d);
aw_gl_func_pointer(compressed_tex_sub_image_3d);
aw_gl_func_pointer(get_compressed_tex_image);
aw_gl_func_pointer(sample_coverage);

/* gl version 1.4 */
aw_gl_func_pointer(blend_color);
aw_gl_func_pointer(blend_equation);
aw_gl_func_pointer(blend_func_separate);
aw_gl_func_pointer(multi_draw_arrays);
aw_gl_func_pointer(multi_draw_elements);
aw_gl_func_pointer(point_parameter_f);
aw_gl_func_pointer(point_parameter_fv);
aw_gl_func_pointer(point_parameter_i);
aw_gl_func_pointer(point_parameter_iv);

/* gl version 1.5 */
aw_gl_func_pointer(begin_query);
aw_gl_func_pointer(bind_buffer);
aw_gl_func_pointer(buffer_data);
aw_gl_func_pointer(buffer_sub_data);
aw_gl_func_pointer(delete_buffers);
aw_gl_func_pointer(delete_queries);
aw_gl_func_pointer(end_query);
aw_gl_func_pointer(gen_buffers);
aw_gl_func_pointer(gen_queries);
aw_gl_func_pointer(get_buffer_parameter_iv);
aw_gl_func_pointer(get_buffer_pointer_v);
aw_gl_func_pointer(get_buffer_sub_data);
aw_gl_func_pointer(get_query_object_iv);
aw_gl_func_pointer(get_query_object_uiv);
aw_gl_func_pointer(get_query_iv);
aw_gl_func_pointer(is_buffer);
aw_gl_func_pointer(is_query);
aw_gl_func_pointer(map_buffer);
aw_gl_func_pointer(unmap_buffer);

/* gl version 2.0 */
aw_gl_func_pointer(attach_shader);
aw_gl_func_pointer(bind_attrib_location);
aw_gl_func_pointer(blend_equation_separate);
aw_gl_func_pointer(compile_shader);
aw_gl_func_pointer(create_program);
aw_gl_func_pointer(create_shader);
aw_gl_func_pointer(delete_program);
aw_gl_func_pointer(delete_shader);
aw_gl_func_pointer(detach_shader);
aw_gl_func_pointer(disable_vertex_attrib_array);
aw_gl_func_pointer(draw_buffers);
aw_gl_func_pointer(enable_vertex_attrib_array);
aw_gl_func_pointer(get_active_attrib);
aw_gl_func_pointer(get_active_uniform);
aw_gl_func_pointer(get_attached_shaders);
aw_gl_func_pointer(get_attrib_location);
aw_gl_func_pointer(get_program_info_log);
aw_gl_func_pointer(get_program_iv);
aw_gl_func_pointer(get_shader_info_log);
aw_gl_func_pointer(get_shader_source);
aw_gl_func_pointer(get_shader_iv);
aw_gl_func_pointer(get_uniform_location);
aw_gl_func_pointer(get_uniform_fv);
aw_gl_func_pointer(get_uniform_iv);
aw_gl_func_pointer(get_vertex_attrib_pointer_v);
aw_gl_func_pointer(get_vertex_attrib_dv);
aw_gl_func_pointer(get_vertex_attrib_fv);
aw_gl_func_pointer(get_vertex_attrib_iv);
aw_gl_func_pointer(is_program);
aw_gl_func_pointer(is_shader);
aw_gl_func_pointer(link_program);
aw_gl_func_pointer(shader_source);
aw_gl_func_pointer(stencil_func_separate);
aw_gl_func_pointer(stencil_mask_separate);
aw_gl_func_pointer(stencil_op_separate);
aw_gl_func_pointer(uniform_1f);
aw_gl_func_pointer(uniform_1fv);
aw_gl_func_pointer(uniform_1i);
aw_gl_func_pointer(uniform_1iv);
aw_gl_func_pointer(uniform_2f);
aw_gl_func_pointer(uniform_2fv);
aw_gl_func_pointer(uniform_2i);
aw_gl_func_pointer(uniform_2iv);
aw_gl_func_pointer(uniform_3f);
aw_gl_func_pointer(uniform_3fv);
aw_gl_func_pointer(uniform_3i);
aw_gl_func_pointer(uniform_3iv);
aw_gl_func_pointer(uniform_4f);
aw_gl_func_pointer(uniform_4fv);
aw_gl_func_pointer(uniform_4i);
aw_gl_func_pointer(uniform_4iv);
aw_gl_func_pointer(uniform_matrix_2fv);
aw_gl_func_pointer(uniform_matrix_3fv);
aw_gl_func_pointer(uniform_matrix_4fv);
aw_gl_func_pointer(use_program);
aw_gl_func_pointer(validate_program);
aw_gl_func_pointer(vertex_attrib_1d);
aw_gl_func_pointer(vertex_attrib_1dv);
aw_gl_func_pointer(vertex_attrib_1f);
aw_gl_func_pointer(vertex_attrib_1fv);
aw_gl_func_pointer(vertex_attrib_1s);
aw_gl_func_pointer(vertex_attrib_1sv);
aw_gl_func_pointer(vertex_attrib_2d);
aw_gl_func_pointer(vertex_attrib_2dv);
aw_gl_func_pointer(vertex_attrib_2f);
aw_gl_func_pointer(vertex_attrib_2fv);
aw_gl_func_pointer(vertex_attrib_2s);
aw_gl_func_pointer(vertex_attrib_2sv);
aw_gl_func_pointer(vertex_attrib_3d);
aw_gl_func_pointer(vertex_attrib_3dv);
aw_gl_func_pointer(vertex_attrib_3f);
aw_gl_func_pointer(vertex_attrib_3fv);
aw_gl_func_pointer(vertex_attrib_3s);
aw_gl_func_pointer(vertex_attrib_3sv);
aw_gl_func_pointer(vertex_attrib_4nbv);
aw_gl_func_pointer(vertex_attrib_4niv);
aw_gl_func_pointer(vertex_attrib_4nsv);
aw_gl_func_pointer(vertex_attrib_4nub);
aw_gl_func_pointer(vertex_attrib_4nubv);
aw_gl_func_pointer(vertex_attrib_4nuiv);
aw_gl_func_pointer(vertex_attrib_4nusv);
aw_gl_func_pointer(vertex_attrib_4bv);
aw_gl_func_pointer(vertex_attrib_4d);
aw_gl_func_pointer(vertex_attrib_4dv);
aw_gl_func_pointer(vertex_attrib_4f);
aw_gl_func_pointer(vertex_attrib_4fv);
aw_gl_func_pointer(vertex_attrib_4iv);
aw_gl_func_pointer(vertex_attrib_4s);
aw_gl_func_pointer(vertex_attrib_4sv);
aw_gl_func_pointer(vertex_attrib_4ubv);
aw_gl_func_pointer(vertex_attrib_4uiv);
aw_gl_func_pointer(vertex_attrib_4usv);
aw_gl_func_pointer(vertex_attrib_pointer);

/* gl version 2.1 */
aw_gl_func_pointer(uniform_matrix_2x3fv);
aw_gl_func_pointer(uniform_matrix_2x4fv);
aw_gl_func_pointer(uniform_matrix_3x2fv);
aw_gl_func_pointer(uniform_matrix_3x4fv);
aw_gl_func_pointer(uniform_matrix_4x2fv);
aw_gl_func_pointer(uniform_matrix_4x3fv);

/* gl version 3.0 */
aw_gl_func_pointer(begin_conditional_render);
aw_gl_func_pointer(begin_transform_feedback);
aw_gl_func_pointer(bind_buffer_base);
aw_gl_func_pointer(bind_buffer_range);
aw_gl_func_pointer(bind_frag_data_location);
aw_gl_func_pointer(bind_framebuffer);
aw_gl_func_pointer(bind_renderbuffer);
aw_gl_func_pointer(bind_vertex_array);
aw_gl_func_pointer(blit_framebuffer);
aw_gl_func_pointer(check_framebuffer_status);
aw_gl_func_pointer(clamp_color);
decltype(clear_bufferf_i) clear_buffer_fi = 0;
aw_gl_func_pointer(clear_buffer_fv);
aw_gl_func_pointer(clear_buffer_iv);
aw_gl_func_pointer(clear_buffer_uiv);
aw_gl_func_pointer(color_mask_i);
aw_gl_func_pointer(delete_framebuffers);
aw_gl_func_pointer(delete_renderbuffers);
aw_gl_func_pointer(delete_vertex_arrays);
aw_gl_func_pointer(disable_i);
aw_gl_func_pointer(enable_i);
aw_gl_func_pointer(end_conditional_render);
aw_gl_func_pointer(end_transform_feedback);
aw_gl_func_pointer(flush_mapped_buffer_range);
aw_gl_func_pointer(framebuffer_renderbuffer);
aw_gl_func_pointer(framebuffer_texture_1d);
aw_gl_func_pointer(framebuffer_texture_2d);
aw_gl_func_pointer(framebuffer_texture_3d);
aw_gl_func_pointer(framebuffer_texture_layer);
aw_gl_func_pointer(gen_framebuffers);
aw_gl_func_pointer(gen_renderbuffers);
aw_gl_func_pointer(gen_vertex_arrays);
aw_gl_func_pointer(generate_mipmap);
aw_gl_func_pointer(get_boolean_iv);
aw_gl_func_pointer(get_frag_data_location);
aw_gl_func_pointer(get_framebuffer_attachment_parameter_iv);
aw_gl_func_pointer(get_integer_iv);
aw_gl_func_pointer(get_renderbuffer_parameter_iv);
aw_gl_func_pointer(get_string_i);
aw_gl_func_pointer(get_tex_parameter_i_iv);
aw_gl_func_pointer(get_tex_parameter_i_uiv);
aw_gl_func_pointer(get_transform_feedback_varying);
aw_gl_func_pointer(get_uniform_uiv);
aw_gl_func_pointer(get_vertex_attrib_i_iv);
aw_gl_func_pointer(get_vertex_attrib_i_uiv);
aw_gl_func_pointer(is_enabled_i);
aw_gl_func_pointer(is_framebuffer);
aw_gl_func_pointer(is_renderbuffer);
aw_gl_func_pointer(is_vertex_array);
aw_gl_func_pointer(map_buffer_range);
aw_gl_func_pointer(renderbuffer_storage);
aw_gl_func_pointer(renderbuffer_storage_multisample);
aw_gl_func_pointer(tex_parameter_i_iv);
aw_gl_func_pointer(tex_parameter_i_uiv);
aw_gl_func_pointer(transform_feedback_varyings);
aw_gl_func_pointer(uniform_1ui);
aw_gl_func_pointer(uniform_1uiv);
aw_gl_func_pointer(uniform_2ui);
aw_gl_func_pointer(uniform_2uiv);
aw_gl_func_pointer(uniform_3ui);
aw_gl_func_pointer(uniform_3uiv);
aw_gl_func_pointer(uniform_4ui);
aw_gl_func_pointer(uniform_4uiv);
aw_gl_func_pointer(vertex_attrib_i_1i);
aw_gl_func_pointer(vertex_attrib_i_1iv);
aw_gl_func_pointer(vertex_attrib_i_1ui);
aw_gl_func_pointer(vertex_attrib_i_1uiv);
aw_gl_func_pointer(vertex_attrib_i_2i);
aw_gl_func_pointer(vertex_attrib_i_2iv);
aw_gl_func_pointer(vertex_attrib_i_2ui);
aw_gl_func_pointer(vertex_attrib_i_2uiv);
aw_gl_func_pointer(vertex_attrib_i_3i);
aw_gl_func_pointer(vertex_attrib_i_3iv);
aw_gl_func_pointer(vertex_attrib_i_3ui);
aw_gl_func_pointer(vertex_attrib_i_3uiv);
aw_gl_func_pointer(vertex_attrib_i_4bv);
aw_gl_func_pointer(vertex_attrib_i_4i);
aw_gl_func_pointer(vertex_attrib_i_4iv);
aw_gl_func_pointer(vertex_attrib_i_4sv);
aw_gl_func_pointer(vertex_attrib_i_4ubv);
aw_gl_func_pointer(vertex_attrib_i_4ui);
aw_gl_func_pointer(vertex_attrib_i_4uiv);
aw_gl_func_pointer(vertex_attrib_i_4usv);
aw_gl_func_pointer(vertex_attrib_i_pointer);

/* gl version 3.1 */
aw_gl_func_pointer(copy_buffer_sub_data);
aw_gl_func_pointer(draw_arrays_instanced);
aw_gl_func_pointer(draw_elements_instanced);
aw_gl_func_pointer(get_active_uniform_block_name);
aw_gl_func_pointer(get_active_uniform_block_iv);
aw_gl_func_pointer(get_active_uniform_name);
aw_gl_func_pointer(get_active_uniforms_iv);
aw_gl_func_pointer(get_uniform_block_index);
aw_gl_func_pointer(get_uniform_indices);
aw_gl_func_pointer(primitive_restart_index);
aw_gl_func_pointer(tex_buffer);
aw_gl_func_pointer(uniform_block_binding);

/* gl version 3.2 */
aw_gl_func_pointer(client_wait_sync);
aw_gl_func_pointer(delete_sync);
aw_gl_func_pointer(draw_elements_base_vertex);
aw_gl_func_pointer(draw_elements_instanced_base_vertex);
aw_gl_func_pointer(draw_range_elements_base_vertex);
aw_gl_func_pointer(fence_sync);
aw_gl_func_pointer(framebuffer_texture);
aw_gl_func_pointer(get_buffer_parameter_i64v);
aw_gl_func_pointer(get_integer_64iv);
aw_gl_func_pointer(get_integer_64v);
aw_gl_func_pointer(get_multisample_fv);
aw_gl_func_pointer(get_sync_iv);
aw_gl_func_pointer(is_sync);
aw_gl_func_pointer(multi_draw_elements_base_vertex);
aw_gl_func_pointer(provoking_vertex);
aw_gl_func_pointer(sample_mask_i);
aw_gl_func_pointer(tex_image_2d_multisample);
aw_gl_func_pointer(tex_image_3d_multisample);
aw_gl_func_pointer(wait_sync);

/* gl version 3.3 */
aw_gl_func_pointer(bind_frag_data_location_indexed);
aw_gl_func_pointer(bind_sampler);
aw_gl_func_pointer(delete_samplers);
aw_gl_func_pointer(gen_samplers);
aw_gl_func_pointer(get_frag_data_index);
aw_gl_func_pointer(get_query_object_i64v);
aw_gl_func_pointer(get_query_object_ui64v);
aw_gl_func_pointer(get_sampler_parameter_i_iv);
aw_gl_func_pointer(get_sampler_parameter_i_uiv);
aw_gl_func_pointer(get_sampler_parameter_fv);
aw_gl_func_pointer(get_sampler_parameter_iv);
aw_gl_func_pointer(is_sampler);
aw_gl_func_pointer(query_counter);
aw_gl_func_pointer(sampler_parameter_i_iv);
aw_gl_func_pointer(sampler_parameter_i_uiv);
aw_gl_func_pointer(sampler_parameter_f);
aw_gl_func_pointer(sampler_parameter_fv);
aw_gl_func_pointer(sampler_parameter_i);
aw_gl_func_pointer(sampler_parameter_iv);
aw_gl_func_pointer(vertex_attrib_divisor);
aw_gl_func_pointer(vertex_attrib_p_1ui);
aw_gl_func_pointer(vertex_attrib_p_1uiv);
aw_gl_func_pointer(vertex_attrib_p_2ui);
aw_gl_func_pointer(vertex_attrib_p_2uiv);
aw_gl_func_pointer(vertex_attrib_p_3ui);
aw_gl_func_pointer(vertex_attrib_p_3uiv);
aw_gl_func_pointer(vertex_attrib_p_4ui);
aw_gl_func_pointer(vertex_attrib_p_4uiv);

/* gl version 4.0 */
aw_gl_func_pointer(begin_query_indexed);
aw_gl_func_pointer(bind_transform_feedback);
aw_gl_func_pointer(blend_equation_separate_i);
aw_gl_func_pointer(blend_equation_i);
aw_gl_func_pointer(blend_func_separate_i);
aw_gl_func_pointer(blend_func_i);
aw_gl_func_pointer(delete_transform_feedbacks);
aw_gl_func_pointer(draw_arrays_indirect);
aw_gl_func_pointer(draw_elements_indirect);
aw_gl_func_pointer(draw_transform_feedback);
aw_gl_func_pointer(draw_transform_feedback_stream);
aw_gl_func_pointer(end_query_indexed);
aw_gl_func_pointer(gen_transform_feedbacks);
aw_gl_func_pointer(get_active_subroutine_name);
aw_gl_func_pointer(get_active_subroutine_uniform_name);
aw_gl_func_pointer(get_active_subroutine_uniform_iv);
aw_gl_func_pointer(get_program_stage_iv);
aw_gl_func_pointer(get_query_indexed_iv);
aw_gl_func_pointer(get_subroutine_index);
aw_gl_func_pointer(get_subroutine_uniform_location);
aw_gl_func_pointer(get_uniform_subroutine_uiv);
aw_gl_func_pointer(get_uniform_dv);
aw_gl_func_pointer(is_transform_feedback);
aw_gl_func_pointer(min_sample_shading);
aw_gl_func_pointer(patch_parameter_fv);
aw_gl_func_pointer(patch_parameter_i);
aw_gl_func_pointer(pause_transform_feedback);
aw_gl_func_pointer(resume_transform_feedback);
aw_gl_func_pointer(uniform_1d);
aw_gl_func_pointer(uniform_1dv);
aw_gl_func_pointer(uniform_2d);
aw_gl_func_pointer(uniform_2dv);
aw_gl_func_pointer(uniform_3d);
aw_gl_func_pointer(uniform_3dv);
aw_gl_func_pointer(uniform_4d);
aw_gl_func_pointer(uniform_4dv);
aw_gl_func_pointer(uniform_matrix_2dv);
aw_gl_func_pointer(uniform_matrix_2x3dv);
aw_gl_func_pointer(uniform_matrix_2x4dv);
aw_gl_func_pointer(uniform_matrix_3dv);
aw_gl_func_pointer(uniform_matrix_3x2dv);
aw_gl_func_pointer(uniform_matrix_3x4dv);
aw_gl_func_pointer(uniform_matrix_4dv);
aw_gl_func_pointer(uniform_matrix_4x2dv);
aw_gl_func_pointer(uniform_matrix_4x3dv);
aw_gl_func_pointer(uniform_subroutines_uiv);

/* gl version 4.1 */
aw_gl_func_pointer(active_shader_program);
aw_gl_func_pointer(bind_program_pipeline);
aw_gl_func_pointer(clear_depth_f);
aw_gl_func_pointer(create_shader_program_v);
aw_gl_func_pointer(delete_program_pipelines);
aw_gl_func_pointer(depth_range_array_v);
aw_gl_func_pointer(depth_range_indexed);
aw_gl_func_pointer(depth_range_f);
aw_gl_func_pointer(gen_program_pipelines);
aw_gl_func_pointer(get_double_iv);
aw_gl_func_pointer(get_float_iv);
aw_gl_func_pointer(get_program_binary);
aw_gl_func_pointer(get_program_pipeline_info_log);
aw_gl_func_pointer(get_program_pipeline_iv);
aw_gl_func_pointer(get_shader_precision_format);
aw_gl_func_pointer(get_vertex_attrib_ldv);
aw_gl_func_pointer(is_program_pipeline);
aw_gl_func_pointer(program_binary);
aw_gl_func_pointer(program_parameter_i);
aw_gl_func_pointer(program_uniform_1d);
aw_gl_func_pointer(program_uniform_1dv);
aw_gl_func_pointer(program_uniform_1f);
aw_gl_func_pointer(program_uniform_1fv);
aw_gl_func_pointer(program_uniform_1i);
aw_gl_func_pointer(program_uniform_1iv);
aw_gl_func_pointer(program_uniform_1ui);
aw_gl_func_pointer(program_uniform_1uiv);
aw_gl_func_pointer(program_uniform_2d);
aw_gl_func_pointer(program_uniform_2dv);
aw_gl_func_pointer(program_uniform_2f);
aw_gl_func_pointer(program_uniform_2fv);
aw_gl_func_pointer(program_uniform_2i);
aw_gl_func_pointer(program_uniform_2iv);
aw_gl_func_pointer(program_uniform_2ui);
aw_gl_func_pointer(program_uniform_2uiv);
aw_gl_func_pointer(program_uniform_3d);
aw_gl_func_pointer(program_uniform_3dv);
aw_gl_func_pointer(program_uniform_3f);
aw_gl_func_pointer(program_uniform_3fv);
aw_gl_func_pointer(program_uniform_3i);
aw_gl_func_pointer(program_uniform_3iv);
aw_gl_func_pointer(program_uniform_3ui);
aw_gl_func_pointer(program_uniform_3uiv);
aw_gl_func_pointer(program_uniform_4d);
aw_gl_func_pointer(program_uniform_4dv);
aw_gl_func_pointer(program_uniform_4f);
aw_gl_func_pointer(program_uniform_4fv);
aw_gl_func_pointer(program_uniform_4i);
aw_gl_func_pointer(program_uniform_4iv);
aw_gl_func_pointer(program_uniform_4ui);
aw_gl_func_pointer(program_uniform_4uiv);
aw_gl_func_pointer(program_uniform_matrix_2dv);
aw_gl_func_pointer(program_uniform_matrix_2fv);
aw_gl_func_pointer(program_uniform_matrix_2x3dv);
aw_gl_func_pointer(program_uniform_matrix_2x3fv);
aw_gl_func_pointer(program_uniform_matrix_2x4dv);
aw_gl_func_pointer(program_uniform_matrix_2x4fv);
aw_gl_func_pointer(program_uniform_matrix_3dv);
aw_gl_func_pointer(program_uniform_matrix_3fv);
aw_gl_func_pointer(program_uniform_matrix_3x2dv);
aw_gl_func_pointer(program_uniform_matrix_3x2fv);
aw_gl_func_pointer(program_uniform_matrix_3x4dv);
aw_gl_func_pointer(program_uniform_matrix_3x4fv);
aw_gl_func_pointer(program_uniform_matrix_4dv);
aw_gl_func_pointer(program_uniform_matrix_4fv);
aw_gl_func_pointer(program_uniform_matrix_4x2dv);
aw_gl_func_pointer(program_uniform_matrix_4x2fv);
aw_gl_func_pointer(program_uniform_matrix_4x3dv);
aw_gl_func_pointer(program_uniform_matrix_4x3fv);
aw_gl_func_pointer(release_shader_compiler);
aw_gl_func_pointer(scissor_array_v);
aw_gl_func_pointer(scissor_indexed);
aw_gl_func_pointer(scissor_indexed_v);
aw_gl_func_pointer(shader_binary);
aw_gl_func_pointer(use_program_stages);
aw_gl_func_pointer(validate_program_pipeline);
aw_gl_func_pointer(vertex_attrib_l1d);
aw_gl_func_pointer(vertex_attrib_l1dv);
aw_gl_func_pointer(vertex_attrib_l2d);
aw_gl_func_pointer(vertex_attrib_l2dv);
aw_gl_func_pointer(vertex_attrib_l3d);
aw_gl_func_pointer(vertex_attrib_l3dv);
aw_gl_func_pointer(vertex_attrib_l4d);
aw_gl_func_pointer(vertex_attrib_l4dv);
aw_gl_func_pointer(vertex_attrib_l_pointer);
aw_gl_func_pointer(viewport_array_v);
aw_gl_func_pointer(viewport_indexed_f);
aw_gl_func_pointer(viewport_indexed_fv);

/* gl version 4.2 */
aw_gl_func_pointer(bind_image_texture);
aw_gl_func_pointer(draw_arrays_instanced_base_instance);
aw_gl_func_pointer(draw_elements_instanced_base_instance);
aw_gl_func_pointer(draw_elements_instanced_base_vertex_base_instance);
aw_gl_func_pointer(draw_transform_feedback_instanced);
aw_gl_func_pointer(draw_transform_feedback_stream_instanced);
aw_gl_func_pointer(get_active_atomic_counter_buffer_iv);
aw_gl_func_pointer(get_internalformat_iv);
aw_gl_func_pointer(memory_barrier);
aw_gl_func_pointer(tex_storage_1d);
aw_gl_func_pointer(tex_storage_2d);
aw_gl_func_pointer(tex_storage_3d);

/* gl version 4.3 */
aw_gl_func_pointer(bind_vertex_buffer);
aw_gl_func_pointer(clear_buffer_data);
aw_gl_func_pointer(clear_buffer_sub_data);
aw_gl_func_pointer(copy_image_sub_data);
aw_gl_func_pointer(debug_message_callback);
aw_gl_func_pointer(debug_message_control);
aw_gl_func_pointer(debug_message_insert);
aw_gl_func_pointer(dispatch_compute);
aw_gl_func_pointer(dispatch_compute_indirect);
aw_gl_func_pointer(framebuffer_parameter_i);
aw_gl_func_pointer(get_debug_message_log);
aw_gl_func_pointer(get_framebuffer_parameter_iv);
aw_gl_func_pointer(get_internalformat_i64v);
aw_gl_func_pointer(get_object_label);
aw_gl_func_pointer(get_object_ptr_label);
aw_gl_func_pointer(get_program_interface_iv);
aw_gl_func_pointer(get_program_resource_index);
aw_gl_func_pointer(get_program_resource_location);
aw_gl_func_pointer(get_program_resource_location_index);
aw_gl_func_pointer(get_program_resource_name);
aw_gl_func_pointer(get_program_resource_iv);
aw_gl_func_pointer(invalidate_buffer_data);
aw_gl_func_pointer(invalidate_buffer_sub_data);
aw_gl_func_pointer(invalidate_framebuffer);
aw_gl_func_pointer(invalidate_sub_framebuffer);
aw_gl_func_pointer(invalidate_tex_image);
aw_gl_func_pointer(invalidate_tex_sub_image);
aw_gl_func_pointer(multi_draw_arrays_indirect);
aw_gl_func_pointer(multi_draw_elements_indirect);
aw_gl_func_pointer(object_label);
aw_gl_func_pointer(object_ptr_label);
aw_gl_func_pointer(pop_debug_group);
aw_gl_func_pointer(push_debug_group);
aw_gl_func_pointer(shader_storage_block_binding);
aw_gl_func_pointer(tex_buffer_range);
aw_gl_func_pointer(tex_storage_2d_multisample);
aw_gl_func_pointer(tex_storage_3d_multisample);
aw_gl_func_pointer(texture_view);
aw_gl_func_pointer(vertex_attrib_binding);
aw_gl_func_pointer(vertex_attrib_format);
aw_gl_func_pointer(vertex_attrib_i_format);
aw_gl_func_pointer(vertex_attrib_l_format);
aw_gl_func_pointer(vertex_binding_divisor);

/* gl version 4.4 */
aw_gl_func_pointer(bind_buffers_base);
aw_gl_func_pointer(bind_buffers_range);
aw_gl_func_pointer(bind_image_textures);
aw_gl_func_pointer(bind_samplers);
aw_gl_func_pointer(bind_textures);
aw_gl_func_pointer(bind_vertex_buffers);
aw_gl_func_pointer(buffer_storage);
aw_gl_func_pointer(clear_tex_image);
aw_gl_func_pointer(clear_tex_sub_image);

/* gl version 4.5 */
aw_gl_func_pointer(bind_texture_unit);
aw_gl_func_pointer(blit_named_framebuffer);
aw_gl_func_pointer(check_named_framebuffer_status);
aw_gl_func_pointer(clear_named_buffer_data);
aw_gl_func_pointer(clear_named_buffer_sub_data);
aw_gl_func_pointer(clear_named_framebuffer_fi);
aw_gl_func_pointer(clear_named_framebuffer_fv);
aw_gl_func_pointer(clear_named_framebuffer_iv);
aw_gl_func_pointer(clear_named_framebuffer_uiv);
aw_gl_func_pointer(clip_control);
aw_gl_func_pointer(compressed_texture_sub_image_1d);
aw_gl_func_pointer(compressed_texture_sub_image_2d);
aw_gl_func_pointer(compressed_texture_sub_image_3d);
aw_gl_func_pointer(copy_named_buffer_sub_data);
aw_gl_func_pointer(copy_texture_sub_image_1d);
aw_gl_func_pointer(copy_texture_sub_image_2d);
aw_gl_func_pointer(copy_texture_sub_image_3d);
aw_gl_func_pointer(create_buffers);
aw_gl_func_pointer(create_framebuffers);
aw_gl_func_pointer(create_program_pipelines);
aw_gl_func_pointer(create_queries);
aw_gl_func_pointer(create_renderbuffers);
aw_gl_func_pointer(create_samplers);
aw_gl_func_pointer(create_textures);
aw_gl_func_pointer(create_transform_feedbacks);
aw_gl_func_pointer(create_vertex_arrays);
aw_gl_func_pointer(disable_vertex_array_attrib);
aw_gl_func_pointer(enable_vertex_array_attrib);
aw_gl_func_pointer(flush_mapped_named_buffer_range);
aw_gl_func_pointer(generate_texture_mipmap);
aw_gl_func_pointer(get_compressed_texture_image);
aw_gl_func_pointer(get_compressed_texture_sub_image);
aw_gl_func_pointer(get_graphics_reset_status);
aw_gl_func_pointer(get_named_buffer_parameter_i64v);
aw_gl_func_pointer(get_named_buffer_parameter_iv);
aw_gl_func_pointer(get_named_buffer_pointer_v);
aw_gl_func_pointer(get_named_buffer_sub_data);
aw_gl_func_pointer(get_named_framebuffer_attachment_parameter_iv);
aw_gl_func_pointer(get_named_framebuffer_parameter_iv);
aw_gl_func_pointer(get_named_renderbuffer_parameter_iv);
aw_gl_func_pointer(get_query_buffer_object_i64v);
aw_gl_func_pointer(get_query_buffer_object_iv);
aw_gl_func_pointer(get_query_buffer_object_ui64v);
aw_gl_func_pointer(get_query_buffer_object_uiv);
aw_gl_func_pointer(get_texture_image);
aw_gl_func_pointer(get_texture_level_parameter_fv);
aw_gl_func_pointer(get_texture_level_parameter_iv);
aw_gl_func_pointer(get_texture_parameter_i_iv);
aw_gl_func_pointer(get_texture_parameter_i_uiv);
aw_gl_func_pointer(get_texture_parameter_fv);
aw_gl_func_pointer(get_texture_parameter_iv);
aw_gl_func_pointer(get_texture_sub_image);
aw_gl_func_pointer(get_transform_feedback_i64v);
aw_gl_func_pointer(get_transform_feedback_i_v);
aw_gl_func_pointer(get_transform_feedback_iv);
aw_gl_func_pointer(get_vertex_array_indexed_64iv);
aw_gl_func_pointer(get_vertex_array_indexed_iv);
aw_gl_func_pointer(get_vertex_array_iv);
aw_gl_func_pointer(getn_compressed_tex_image);
aw_gl_func_pointer(getn_tex_image);
aw_gl_func_pointer(getn_uniform_dv);
aw_gl_func_pointer(getn_uniform_fv);
aw_gl_func_pointer(getn_uniform_iv);
aw_gl_func_pointer(getn_uniform_uiv);
aw_gl_func_pointer(invalidate_named_framebuffer_data);
aw_gl_func_pointer(invalidate_named_framebuffer_sub_data);
aw_gl_func_pointer(map_named_buffer);
aw_gl_func_pointer(map_named_buffer_range);
aw_gl_func_pointer(memory_barrier_by_region);
aw_gl_func_pointer(named_buffer_data);
aw_gl_func_pointer(named_buffer_storage);
aw_gl_func_pointer(named_buffer_sub_data);
aw_gl_func_pointer(named_framebuffer_draw_buffer);
aw_gl_func_pointer(named_framebuffer_draw_buffers);
aw_gl_func_pointer(named_framebuffer_parameter_i);
aw_gl_func_pointer(named_framebuffer_read_buffer);
aw_gl_func_pointer(named_framebuffer_renderbuffer);
aw_gl_func_pointer(named_framebuffer_texture);
aw_gl_func_pointer(named_framebuffer_texture_layer);
aw_gl_func_pointer(named_renderbuffer_storage);
aw_gl_func_pointer(named_renderbuffer_storage_multisample);
aw_gl_func_pointer(read_n_pixels);
aw_gl_func_pointer(texture_barrier);
aw_gl_func_pointer(texture_buffer);
aw_gl_func_pointer(texture_buffer_range);
aw_gl_func_pointer(texture_parameter_i_iv);
aw_gl_func_pointer(texture_parameter_i_uiv);
aw_gl_func_pointer(texture_parameter_f);
aw_gl_func_pointer(texture_parameter_fv);
aw_gl_func_pointer(texture_parameter_i);
aw_gl_func_pointer(texture_parameter_iv);
aw_gl_func_pointer(texture_storage_1d);
aw_gl_func_pointer(texture_storage_2d);
aw_gl_func_pointer(texture_storage_2d_multisample);
aw_gl_func_pointer(texture_storage_3d);
aw_gl_func_pointer(texture_storage_3d_multisample);
aw_gl_func_pointer(texture_sub_image_1d);
aw_gl_func_pointer(texture_sub_image_2d);
aw_gl_func_pointer(texture_sub_image_3d);
aw_gl_func_pointer(transform_feedback_buffer_base);
aw_gl_func_pointer(transform_feedback_buffer_range);
aw_gl_func_pointer(unmap_named_buffer);
aw_gl_func_pointer(vertex_array_attrib_binding);
aw_gl_func_pointer(vertex_array_attrib_format);
aw_gl_func_pointer(vertex_array_attrib_i_format);
aw_gl_func_pointer(vertex_array_attrib_l_format);
aw_gl_func_pointer(vertex_array_binding_divisor);
aw_gl_func_pointer(vertex_array_element_buffer);
aw_gl_func_pointer(vertex_array_vertex_buffer);
aw_gl_func_pointer(vertex_array_vertex_buffers);

/* gl version 4.6 */
aw_gl_func_pointer(multi_draw_arrays_indirect_count);
aw_gl_func_pointer(multi_draw_elements_indirect_count);
aw_gl_func_pointer(polygon_offset_clamp);
aw_gl_func_pointer(specialize_shader);

namespace {
int load_gl_3_2_functions()
{
	int num_failed = 0;
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(blend_func, "glBlendFunc");
	core_load_func(clear, "glClear");
	core_load_func(clear_color, "glClearColor");
	core_load_func(clear_depth, "glClearDepth");
	core_load_func(clear_stencil, "glClearStencil");
	core_load_func(color_mask, "glColorMask");
	core_load_func(cull_face, "glCullFace");
	core_load_func(depth_func, "glDepthFunc");
	core_load_func(depth_mask, "glDepthMask");
	core_load_func(depth_range, "glDepthRange");
	core_load_func(disable, "glDisable");
	core_load_func(draw_buffer, "glDrawBuffer");
	core_load_func(enable, "glEnable");
	core_load_func(finish, "glFinish");
	core_load_func(flush, "glFlush");
	core_load_func(front_face, "glFrontFace");
	core_load_func(get_boolean_v, "glGetBooleanv");
	core_load_func(get_double_v, "glGetDoublev");
	core_load_func(get_error, "glGetError");
	core_load_func(get_float_v, "glGetFloatv");
	core_load_func(get_integer_v, "glGetIntegerv");
	core_load_func(get_string, "glGetString");
	core_load_func(get_tex_image, "glGetTexImage");
	core_load_func(get_tex_level_parameter_fv, "glGetTexLevelParameterfv");
	core_load_func(get_tex_level_parameter_iv, "glGetTexLevelParameteriv");
	core_load_func(get_tex_parameter_fv, "glGetTexParameterfv");
	core_load_func(get_tex_parameter_iv, "glGetTexParameteriv");
	core_load_func(hint, "glHint");
	core_load_func(is_enabled, "glIsEnabled");
	core_load_func(line_width, "glLineWidth");
	core_load_func(logic_op, "glLogicOp");
	core_load_func(pixel_store_f, "glPixelStoref");
	core_load_func(pixel_store_i, "glPixelStorei");
	core_load_func(point_size, "glPointSize");
	core_load_func(polygon_mode, "glPolygonMode");
	core_load_func(read_buffer, "glReadBuffer");
	core_load_func(read_pixels, "glReadPixels");
	core_load_func(scissor, "glScissor");
	core_load_func(stencil_func, "glStencilFunc");
	core_load_func(stencil_mask, "glStencilMask");
	core_load_func(stencil_op, "glStencilOp");
	core_load_func(tex_image_1d, "glTexImage1D");
	core_load_func(tex_image_2d, "glTexImage2D");
	core_load_func(tex_parameter_f, "glTexParameterf");
	core_load_func(tex_parameter_fv, "glTexParameterfv");
	core_load_func(tex_parameter_i, "glTexParameteri");
	core_load_func(tex_parameter_iv, "glTexParameteriv");
	core_load_func(viewport, "glViewport");
	core_load_func(bind_texture, "glBindTexture");
	core_load_func(copy_tex_image_1d, "glCopyTexImage1D");
	core_load_func(copy_tex_image_2d, "glCopyTexImage2D");
	core_load_func(copy_tex_sub_image_1d, "glCopyTexSubImage1D");
	core_load_func(copy_tex_sub_image_2d, "glCopyTexSubImage2D");
	core_load_func(delete_textures, "glDeleteTextures");
	core_load_func(draw_arrays, "glDrawArrays");
	core_load_func(draw_elements, "glDrawElements");
	core_load_func(gen_textures, "glGenTextures");
	core_load_func(get_pointer_v, "glGetPointerv");
	core_load_func(is_texture, "glIsTexture");
	core_load_func(polygon_offset, "glPolygonOffset");
	core_load_func(tex_sub_image_1d, "glTexSubImage1D");
	core_load_func(tex_sub_image_2d, "glTexSubImage2D");
	core_load_func(copy_tex_sub_image_3d, "glCopyTexSubImage3D");
	core_load_func(draw_range_elements, "glDrawRangeElements");
	core_load_func(tex_image_3d, "glTexImage3D");
	core_load_func(tex_sub_image_3d, "glTexSubImage3D");
	core_load_func(active_texture, "glActiveTexture");
	core_load_func(compressed_tex_image_1d, "glCompressedTexImage1D");
	core_load_func(compressed_tex_image_2d, "glCompressedTexImage2D");
	core_load_func(compressed_tex_image_3d, "glCompressedTexImage3D");
	core_load_func(compressed_tex_sub_image_1d, "glCompressedTexSubImage1D");
	core_load_func(compressed_tex_sub_image_2d, "glCompressedTexSubImage2D");
	core_load_func(compressed_tex_sub_image_3d, "glCompressedTexSubImage3D");
	core_load_func(get_compressed_tex_image, "glGetCompressedTexImage");
	core_load_func(sample_coverage, "glSampleCoverage");
	core_load_func(blend_color, "glBlendColor");
	core_load_func(blend_equation, "glBlendEquation");
	core_load_func(blend_func_separate, "glBlendFuncSeparate");
	core_load_func(multi_draw_arrays, "glMultiDrawArrays");
	core_load_func(multi_draw_elements, "glMultiDrawElements");
	core_load_func(point_parameter_f, "glPointParameterf");
	core_load_func(point_parameter_fv, "glPointParameterfv");
	core_load_func(point_parameter_i, "glPointParameteri");
	core_load_func(point_parameter_iv, "glPointParameteriv");
	core_load_func(begin_query, "glBeginQuery");
	core_load_func(bind_buffer, "glBindBuffer");
	core_load_func(buffer_data, "glBufferData");
	core_load_func(buffer_sub_data, "glBufferSubData");
	core_load_func(delete_buffers, "glDeleteBuffers");
	core_load_func(delete_queries, "glDeleteQueries");
	core_load_func(end_query, "glEndQuery");
	core_load_func(gen_buffers, "glGenBuffers");
	core_load_func(gen_queries, "glGenQueries");
	core_load_func(get_buffer_parameter_iv, "glGetBufferParameteriv");
	core_load_func(get_buffer_pointer_v, "glGetBufferPointerv");
	core_load_func(get_buffer_sub_data, "glGetBufferSubData");
	core_load_func(get_query_object_iv, "glGetQueryObjectiv");
	core_load_func(get_query_object_uiv, "glGetQueryObjectuiv");
	core_load_func(get_query_iv, "glGetQueryiv");
	core_load_func(is_buffer, "glIsBuffer");
	core_load_func(is_query, "glIsQuery");
	core_load_func(map_buffer, "glMapBuffer");
	core_load_func(unmap_buffer, "glUnmapBuffer");
	core_load_func(attach_shader, "glAttachShader");
	core_load_func(bind_attrib_location, "glBindAttribLocation");
	core_load_func(blend_equation_separate, "glBlendEquationSeparate");
	core_load_func(compile_shader, "glCompileShader");
	core_load_func(create_program, "glCreateProgram");
	core_load_func(create_shader, "glCreateShader");
	core_load_func(delete_program, "glDeleteProgram");
	core_load_func(delete_shader, "glDeleteShader");
	core_load_func(detach_shader, "glDetachShader");
	core_load_func(disable_vertex_attrib_array, "glDisableVertexAttribArray");
	core_load_func(draw_buffers, "glDrawBuffers");
	core_load_func(enable_vertex_attrib_array, "glEnableVertexAttribArray");
	core_load_func(get_active_attrib, "glGetActiveAttrib");
	core_load_func(get_active_uniform, "glGetActiveUniform");
	core_load_func(get_attached_shaders, "glGetAttachedShaders");
	core_load_func(get_attrib_location, "glGetAttribLocation");
	core_load_func(get_program_info_log, "glGetProgramInfoLog");
	core_load_func(get_program_iv, "glGetProgramiv");
	core_load_func(get_shader_info_log, "glGetShaderInfoLog");
	core_load_func(get_shader_source, "glGetShaderSource");
	core_load_func(get_shader_iv, "glGetShaderiv");
	core_load_func(get_uniform_location, "glGetUniformLocation");
	core_load_func(get_uniform_fv, "glGetUniformfv");
	core_load_func(get_uniform_iv, "glGetUniformiv");
	core_load_func(get_vertex_attrib_pointer_v, "glGetVertexAttribPointerv");
	core_load_func(get_vertex_attrib_dv, "glGetVertexAttribdv");
	core_load_func(get_vertex_attrib_fv, "glGetVertexAttribfv");
	core_load_func(get_vertex_attrib_iv, "glGetVertexAttribiv");
	core_load_func(is_program, "glIsProgram");
	core_load_func(is_shader, "glIsShader");
	core_load_func(link_program, "glLinkProgram");
	core_load_func(shader_source, "glShaderSource");
	core_load_func(stencil_func_separate, "glStencilFuncSeparate");
	core_load_func(stencil_mask_separate, "glStencilMaskSeparate");
	core_load_func(stencil_op_separate, "glStencilOpSeparate");
	core_load_func(uniform_1f, "glUniform1f");
	core_load_func(uniform_1fv, "glUniform1fv");
	core_load_func(uniform_1i, "glUniform1i");
	core_load_func(uniform_1iv, "glUniform1iv");
	core_load_func(uniform_2f, "glUniform2f");
	core_load_func(uniform_2fv, "glUniform2fv");
	core_load_func(uniform_2i, "glUniform2i");
	core_load_func(uniform_2iv, "glUniform2iv");
	core_load_func(uniform_3f, "glUniform3f");
	core_load_func(uniform_3fv, "glUniform3fv");
	core_load_func(uniform_3i, "glUniform3i");
	core_load_func(uniform_3iv, "glUniform3iv");
	core_load_func(uniform_4f, "glUniform4f");
	core_load_func(uniform_4fv, "glUniform4fv");
	core_load_func(uniform_4i, "glUniform4i");
	core_load_func(uniform_4iv, "glUniform4iv");
	core_load_func(uniform_matrix_2fv, "glUniformMatrix2fv");
	core_load_func(uniform_matrix_3fv, "glUniformMatrix3fv");
	core_load_func(uniform_matrix_4fv, "glUniformMatrix4fv");
	core_load_func(use_program, "glUseProgram");
	core_load_func(validate_program, "glValidateProgram");
	core_load_func(vertex_attrib_1d, "glVertexAttrib1d");
	core_load_func(vertex_attrib_1dv, "glVertexAttrib1dv");
	core_load_func(vertex_attrib_1f, "glVertexAttrib1f");
	core_load_func(vertex_attrib_1fv, "glVertexAttrib1fv");
	core_load_func(vertex_attrib_1s, "glVertexAttrib1s");
	core_load_func(vertex_attrib_1sv, "glVertexAttrib1sv");
	core_load_func(vertex_attrib_2d, "glVertexAttrib2d");
	core_load_func(vertex_attrib_2dv, "glVertexAttrib2dv");
	core_load_func(vertex_attrib_2f, "glVertexAttrib2f");
	core_load_func(vertex_attrib_2fv, "glVertexAttrib2fv");
	core_load_func(vertex_attrib_2s, "glVertexAttrib2s");
	core_load_func(vertex_attrib_2sv, "glVertexAttrib2sv");
	core_load_func(vertex_attrib_3d, "glVertexAttrib3d");
	core_load_func(vertex_attrib_3dv, "glVertexAttrib3dv");
	core_load_func(vertex_attrib_3f, "glVertexAttrib3f");
	core_load_func(vertex_attrib_3fv, "glVertexAttrib3fv");
	core_load_func(vertex_attrib_3s, "glVertexAttrib3s");
	core_load_func(vertex_attrib_3sv, "glVertexAttrib3sv");
	core_load_func(vertex_attrib_4nbv, "glVertexAttrib4Nbv");
	core_load_func(vertex_attrib_4niv, "glVertexAttrib4Niv");
	core_load_func(vertex_attrib_4nsv, "glVertexAttrib4Nsv");
	core_load_func(vertex_attrib_4nub, "glVertexAttrib4Nub");
	core_load_func(vertex_attrib_4nubv, "glVertexAttrib4Nubv");
	core_load_func(vertex_attrib_4nuiv, "glVertexAttrib4Nuiv");
	core_load_func(vertex_attrib_4nusv, "glVertexAttrib4Nusv");
	core_load_func(vertex_attrib_4bv, "glVertexAttrib4bv");
	core_load_func(vertex_attrib_4d, "glVertexAttrib4d");
	core_load_func(vertex_attrib_4dv, "glVertexAttrib4dv");
	core_load_func(vertex_attrib_4f, "glVertexAttrib4f");
	core_load_func(vertex_attrib_4fv, "glVertexAttrib4fv");
	core_load_func(vertex_attrib_4iv, "glVertexAttrib4iv");
	core_load_func(vertex_attrib_4s, "glVertexAttrib4s");
	core_load_func(vertex_attrib_4sv, "glVertexAttrib4sv");
	core_load_func(vertex_attrib_4ubv, "glVertexAttrib4ubv");
	core_load_func(vertex_attrib_4uiv, "glVertexAttrib4uiv");
	core_load_func(vertex_attrib_4usv, "glVertexAttrib4usv");
	core_load_func(vertex_attrib_pointer, "glVertexAttribPointer");
	core_load_func(uniform_matrix_2x3fv, "glUniformMatrix2x3fv");
	core_load_func(uniform_matrix_2x4fv, "glUniformMatrix2x4fv");
	core_load_func(uniform_matrix_3x2fv, "glUniformMatrix3x2fv");
	core_load_func(uniform_matrix_3x4fv, "glUniformMatrix3x4fv");
	core_load_func(uniform_matrix_4x2fv, "glUniformMatrix4x2fv");
	core_load_func(uniform_matrix_4x3fv, "glUniformMatrix4x3fv");
	core_load_func(begin_conditional_render, "glBeginConditionalRender");
	core_load_func(begin_transform_feedback, "glBeginTransformFeedback");
	core_load_func(bind_buffer_base, "glBindBufferBase");
	core_load_func(bind_buffer_range, "glBindBufferRange");
	core_load_func(bind_frag_data_location, "glBindFragDataLocation");
	core_load_func(bind_framebuffer, "glBindFramebuffer");
	core_load_func(bind_renderbuffer, "glBindRenderbuffer");
	core_load_func(bind_vertex_array, "glBindVertexArray");
	core_load_func(blit_framebuffer, "glBlitFramebuffer");
	core_load_func(check_framebuffer_status, "glCheckFramebufferStatus");
	core_load_func(clamp_color, "glClampColor");
	core_load_func(clear_buffer_fi, "glClearBufferfi");
	core_load_func(clear_buffer_fv, "glClearBufferfv");
	core_load_func(clear_buffer_iv, "glClearBufferiv");
	core_load_func(clear_buffer_uiv, "glClearBufferuiv");
	core_load_func(color_mask_i, "glColorMaski");
	core_load_func(delete_framebuffers, "glDeleteFramebuffers");
	core_load_func(delete_renderbuffers, "glDeleteRenderbuffers");
	core_load_func(delete_vertex_arrays, "glDeleteVertexArrays");
	core_load_func(disable_i, "glDisablei");
	core_load_func(enable_i, "glEnablei");
	core_load_func(end_conditional_render, "glEndConditionalRender");
	core_load_func(end_transform_feedback, "glEndTransformFeedback");
	core_load_func(flush_mapped_buffer_range, "glFlushMappedBufferRange");
	core_load_func(framebuffer_renderbuffer, "glFramebufferRenderbuffer");
	core_load_func(framebuffer_texture_1d, "glFramebufferTexture1D");
	core_load_func(framebuffer_texture_2d, "glFramebufferTexture2D");
	core_load_func(framebuffer_texture_3d, "glFramebufferTexture3D");
	core_load_func(framebuffer_texture_layer, "glFramebufferTextureLayer");
	core_load_func(gen_framebuffers, "glGenFramebuffers");
	core_load_func(gen_renderbuffers, "glGenRenderbuffers");
	core_load_func(gen_vertex_arrays, "glGenVertexArrays");
	core_load_func(generate_mipmap, "glGenerateMipmap");
	core_load_func(get_boolean_iv, "glGetBooleani_v");
	core_load_func(get_frag_data_location, "glGetFragDataLocation");
	core_load_func(get_framebuffer_attachment_parameter_iv, "glGetFramebufferAttachmentParameteriv");
	core_load_func(get_integer_iv, "glGetIntegeri_v");
	core_load_func(get_renderbuffer_parameter_iv, "glGetRenderbufferParameteriv");
	core_load_func(get_string_i, "glGetStringi");
	core_load_func(get_tex_parameter_i_iv, "glGetTexParameterIiv");
	core_load_func(get_tex_parameter_i_uiv, "glGetTexParameterIuiv");
	core_load_func(get_transform_feedback_varying, "glGetTransformFeedbackVarying");
	core_load_func(get_uniform_uiv, "glGetUniformuiv");
	core_load_func(get_vertex_attrib_i_iv, "glGetVertexAttribIiv");
	core_load_func(get_vertex_attrib_i_uiv, "glGetVertexAttribIuiv");
	core_load_func(is_enabled_i, "glIsEnabledi");
	core_load_func(is_framebuffer, "glIsFramebuffer");
	core_load_func(is_renderbuffer, "glIsRenderbuffer");
	core_load_func(is_vertex_array, "glIsVertexArray");
	core_load_func(map_buffer_range, "glMapBufferRange");
	core_load_func(renderbuffer_storage, "glRenderbufferStorage");
	core_load_func(renderbuffer_storage_multisample, "glRenderbufferStorageMultisample");
	core_load_func(tex_parameter_i_iv, "glTexParameterIiv");
	core_load_func(tex_parameter_i_uiv, "glTexParameterIuiv");
	core_load_func(transform_feedback_varyings, "glTransformFeedbackVaryings");
	core_load_func(uniform_1ui, "glUniform1ui");
	core_load_func(uniform_1uiv, "glUniform1uiv");
	core_load_func(uniform_2ui, "glUniform2ui");
	core_load_func(uniform_2uiv, "glUniform2uiv");
	core_load_func(uniform_3ui, "glUniform3ui");
	core_load_func(uniform_3uiv, "glUniform3uiv");
	core_load_func(uniform_4ui, "glUniform4ui");
	core_load_func(uniform_4uiv, "glUniform4uiv");
	core_load_func(vertex_attrib_i_1i, "glVertexAttribI1i");
	core_load_func(vertex_attrib_i_1iv, "glVertexAttribI1iv");
	core_load_func(vertex_attrib_i_1ui, "glVertexAttribI1ui");
	core_load_func(vertex_attrib_i_1uiv, "glVertexAttribI1uiv");
	core_load_func(vertex_attrib_i_2i, "glVertexAttribI2i");
	core_load_func(vertex_attrib_i_2iv, "glVertexAttribI2iv");
	core_load_func(vertex_attrib_i_2ui, "glVertexAttribI2ui");
	core_load_func(vertex_attrib_i_2uiv, "glVertexAttribI2uiv");
	core_load_func(vertex_attrib_i_3i, "glVertexAttribI3i");
	core_load_func(vertex_attrib_i_3iv, "glVertexAttribI3iv");
	core_load_func(vertex_attrib_i_3ui, "glVertexAttribI3ui");
	core_load_func(vertex_attrib_i_3uiv, "glVertexAttribI3uiv");
	core_load_func(vertex_attrib_i_4bv, "glVertexAttribI4bv");
	core_load_func(vertex_attrib_i_4i, "glVertexAttribI4i");
	core_load_func(vertex_attrib_i_4iv, "glVertexAttribI4iv");
	core_load_func(vertex_attrib_i_4sv, "glVertexAttribI4sv");
	core_load_func(vertex_attrib_i_4ubv, "glVertexAttribI4ubv");
	core_load_func(vertex_attrib_i_4ui, "glVertexAttribI4ui");
	core_load_func(vertex_attrib_i_4uiv, "glVertexAttribI4uiv");
	core_load_func(vertex_attrib_i_4usv, "glVertexAttribI4usv");
	core_load_func(vertex_attrib_i_pointer, "glVertexAttribIPointer");
	core_load_func(copy_buffer_sub_data, "glCopyBufferSubData");
	core_load_func(draw_arrays_instanced, "glDrawArraysInstanced");
	core_load_func(draw_elements_instanced, "glDrawElementsInstanced");
	core_load_func(get_active_uniform_block_name, "glGetActiveUniformBlockName");
	core_load_func(get_active_uniform_block_iv, "glGetActiveUniformBlockiv");
	core_load_func(get_active_uniform_name, "glGetActiveUniformName");
	core_load_func(get_active_uniforms_iv, "glGetActiveUniformsiv");
	core_load_func(get_uniform_block_index, "glGetUniformBlockIndex");
	core_load_func(get_uniform_indices, "glGetUniformIndices");
	core_load_func(primitive_restart_index, "glPrimitiveRestartIndex");
	core_load_func(tex_buffer, "glTexBuffer");
	core_load_func(uniform_block_binding, "glUniformBlockBinding");
	core_load_func(client_wait_sync, "glClientWaitSync");
	core_load_func(delete_sync, "glDeleteSync");
	core_load_func(draw_elements_base_vertex, "glDrawElementsBaseVertex");
	core_load_func(draw_elements_instanced_base_vertex, "glDrawElementsInstancedBaseVertex");
	core_load_func(draw_range_elements_base_vertex, "glDrawRangeElementsBaseVertex");
	core_load_func(fence_sync, "glFenceSync");
	core_load_func(framebuffer_texture, "glFramebufferTexture");
	core_load_func(get_buffer_parameter_i64v, "glGetBufferParameteri64v");
	core_load_func(get_integer_64iv, "glGetInteger64i_v");
	core_load_func(get_integer_64v, "glGetInteger64v");
	core_load_func(get_multisample_fv, "glGetMultisamplefv");
	core_load_func(get_sync_iv, "glGetSynciv");
	core_load_func(is_sync, "glIsSync");
	core_load_func(multi_draw_elements_base_vertex, "glMultiDrawElementsBaseVertex");
	core_load_func(provoking_vertex, "glProvokingVertex");
	core_load_func(sample_mask_i, "glSampleMaski");
	core_load_func(tex_image_2d_multisample, "glTexImage2DMultisample");
	core_load_func(tex_image_3d_multisample, "glTexImage3DMultisample");
	core_load_func(wait_sync, "glWaitSync");
	return num_failed;
}

int load_gl_3_3_functions()
{
	int num_failed = load_gl_3_2_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(bind_frag_data_location_indexed, "glBindFragDataLocationIndexed");
	core_load_func(bind_sampler, "glBindSampler");
	core_load_func(delete_samplers, "glDeleteSamplers");
	core_load_func(gen_samplers, "glGenSamplers");
	core_load_func(get_frag_data_index, "glGetFragDataIndex");
	core_load_func(get_query_object_i64v, "glGetQueryObjecti64v");
	core_load_func(get_query_object_ui64v, "glGetQueryObjectui64v");
	core_load_func(get_sampler_parameter_i_iv, "glGetSamplerParameterIiv");
	core_load_func(get_sampler_parameter_i_uiv, "glGetSamplerParameterIuiv");
	core_load_func(get_sampler_parameter_fv, "glGetSamplerParameterfv");
	core_load_func(get_sampler_parameter_iv, "glGetSamplerParameteriv");
	core_load_func(is_sampler, "glIsSampler");
	core_load_func(query_counter, "glQueryCounter");
	core_load_func(sampler_parameter_i_iv, "glSamplerParameterIiv");
	core_load_func(sampler_parameter_i_uiv, "glSamplerParameterIuiv");
	core_load_func(sampler_parameter_f, "glSamplerParameterf");
	core_load_func(sampler_parameter_fv, "glSamplerParameterfv");
	core_load_func(sampler_parameter_i, "glSamplerParameteri");
	core_load_func(sampler_parameter_iv, "glSamplerParameteriv");
	core_load_func(vertex_attrib_divisor, "glVertexAttribDivisor");
	core_load_func(vertex_attrib_p_1ui, "glVertexAttribP1ui");
	core_load_func(vertex_attrib_p_1uiv, "glVertexAttribP1uiv");
	core_load_func(vertex_attrib_p_2ui, "glVertexAttribP2ui");
	core_load_func(vertex_attrib_p_2uiv, "glVertexAttribP2uiv");
	core_load_func(vertex_attrib_p_3ui, "glVertexAttribP3ui");
	core_load_func(vertex_attrib_p_3uiv, "glVertexAttribP3uiv");
	core_load_func(vertex_attrib_p_4ui, "glVertexAttribP4ui");
	core_load_func(vertex_attrib_p_4uiv, "glVertexAttribP4uiv");
	return num_failed;
}

int load_gl_4_0_functions()
{
	int num_failed = load_gl_3_3_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(begin_query_indexed, "glBeginQueryIndexed");
	core_load_func(bind_transform_feedback, "glBindTransformFeedback");
	core_load_func(blend_equation_separate_i, "glBlendEquationSeparatei");
	core_load_func(blend_equation_i, "glBlendEquationi");
	core_load_func(blend_func_separate_i, "glBlendFuncSeparatei");
	core_load_func(blend_func_i, "glBlendFunci");
	core_load_func(delete_transform_feedbacks, "glDeleteTransformFeedbacks");
	core_load_func(draw_arrays_indirect, "glDrawArraysIndirect");
	core_load_func(draw_elements_indirect, "glDrawElementsIndirect");
	core_load_func(draw_transform_feedback, "glDrawTransformFeedback");
	core_load_func(draw_transform_feedback_stream, "glDrawTransformFeedbackStream");
	core_load_func(end_query_indexed, "glEndQueryIndexed");
	core_load_func(gen_transform_feedbacks, "glGenTransformFeedbacks");
	core_load_func(get_active_subroutine_name, "glGetActiveSubroutineName");
	core_load_func(get_active_subroutine_uniform_name, "glGetActiveSubroutineUniformName");
	core_load_func(get_active_subroutine_uniform_iv, "glGetActiveSubroutineUniformiv");
	core_load_func(get_program_stage_iv, "glGetProgramStageiv");
	core_load_func(get_query_indexed_iv, "glGetQueryIndexediv");
	core_load_func(get_subroutine_index, "glGetSubroutineIndex");
	core_load_func(get_subroutine_uniform_location, "glGetSubroutineUniformLocation");
	core_load_func(get_uniform_subroutine_uiv, "glGetUniformSubroutineuiv");
	core_load_func(get_uniform_dv, "glGetUniformdv");
	core_load_func(is_transform_feedback, "glIsTransformFeedback");
	core_load_func(min_sample_shading, "glMinSampleShading");
	core_load_func(patch_parameter_fv, "glPatchParameterfv");
	core_load_func(patch_parameter_i, "glPatchParameteri");
	core_load_func(pause_transform_feedback, "glPauseTransformFeedback");
	core_load_func(resume_transform_feedback, "glResumeTransformFeedback");
	core_load_func(uniform_1d, "glUniform1d");
	core_load_func(uniform_1dv, "glUniform1dv");
	core_load_func(uniform_2d, "glUniform2d");
	core_load_func(uniform_2dv, "glUniform2dv");
	core_load_func(uniform_3d, "glUniform3d");
	core_load_func(uniform_3dv, "glUniform3dv");
	core_load_func(uniform_4d, "glUniform4d");
	core_load_func(uniform_4dv, "glUniform4dv");
	core_load_func(uniform_matrix_2dv, "glUniformMatrix2dv");
	core_load_func(uniform_matrix_2x3dv, "glUniformMatrix2x3dv");
	core_load_func(uniform_matrix_2x4dv, "glUniformMatrix2x4dv");
	core_load_func(uniform_matrix_3dv, "glUniformMatrix3dv");
	core_load_func(uniform_matrix_3x2dv, "glUniformMatrix3x2dv");
	core_load_func(uniform_matrix_3x4dv, "glUniformMatrix3x4dv");
	core_load_func(uniform_matrix_4dv, "glUniformMatrix4dv");
	core_load_func(uniform_matrix_4x2dv, "glUniformMatrix4x2dv");
	core_load_func(uniform_matrix_4x3dv, "glUniformMatrix4x3dv");
	core_load_func(uniform_subroutines_uiv, "glUniformSubroutinesuiv");
	return num_failed;
}

int load_gl_4_1_functions()
{
	int num_failed = load_gl_4_0_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(active_shader_program, "glActiveShaderProgram");
	core_load_func(bind_program_pipeline, "glBindProgramPipeline");
	core_load_func(clear_depth_f, "glClearDepthf");
	core_load_func(create_shader_program_v, "glCreateShaderProgramv");
	core_load_func(delete_program_pipelines, "glDeleteProgramPipelines");
	core_load_func(depth_range_array_v, "glDepthRangeArrayv");
	core_load_func(depth_range_indexed, "glDepthRangeIndexed");
	core_load_func(depth_range_f, "glDepthRangef");
	core_load_func(gen_program_pipelines, "glGenProgramPipelines");
	core_load_func(get_double_iv, "glGetDoublei_v");
	core_load_func(get_float_iv, "glGetFloati_v");
	core_load_func(get_program_binary, "glGetProgramBinary");
	core_load_func(get_program_pipeline_info_log, "glGetProgramPipelineInfoLog");
	core_load_func(get_program_pipeline_iv, "glGetProgramPipelineiv");
	core_load_func(get_shader_precision_format, "glGetShaderPrecisionFormat");
	core_load_func(get_vertex_attrib_ldv, "glGetVertexAttribLdv");
	core_load_func(is_program_pipeline, "glIsProgramPipeline");
	core_load_func(program_binary, "glProgramBinary");
	core_load_func(program_parameter_i, "glProgramParameteri");
	core_load_func(program_uniform_1d, "glProgramUniform1d");
	core_load_func(program_uniform_1dv, "glProgramUniform1dv");
	core_load_func(program_uniform_1f, "glProgramUniform1f");
	core_load_func(program_uniform_1fv, "glProgramUniform1fv");
	core_load_func(program_uniform_1i, "glProgramUniform1i");
	core_load_func(program_uniform_1iv, "glProgramUniform1iv");
	core_load_func(program_uniform_1ui, "glProgramUniform1ui");
	core_load_func(program_uniform_1uiv, "glProgramUniform1uiv");
	core_load_func(program_uniform_2d, "glProgramUniform2d");
	core_load_func(program_uniform_2dv, "glProgramUniform2dv");
	core_load_func(program_uniform_2f, "glProgramUniform2f");
	core_load_func(program_uniform_2fv, "glProgramUniform2fv");
	core_load_func(program_uniform_2i, "glProgramUniform2i");
	core_load_func(program_uniform_2iv, "glProgramUniform2iv");
	core_load_func(program_uniform_2ui, "glProgramUniform2ui");
	core_load_func(program_uniform_2uiv, "glProgramUniform2uiv");
	core_load_func(program_uniform_3d, "glProgramUniform3d");
	core_load_func(program_uniform_3dv, "glProgramUniform3dv");
	core_load_func(program_uniform_3f, "glProgramUniform3f");
	core_load_func(program_uniform_3fv, "glProgramUniform3fv");
	core_load_func(program_uniform_3i, "glProgramUniform3i");
	core_load_func(program_uniform_3iv, "glProgramUniform3iv");
	core_load_func(program_uniform_3ui, "glProgramUniform3ui");
	core_load_func(program_uniform_3uiv, "glProgramUniform3uiv");
	core_load_func(program_uniform_4d, "glProgramUniform4d");
	core_load_func(program_uniform_4dv, "glProgramUniform4dv");
	core_load_func(program_uniform_4f, "glProgramUniform4f");
	core_load_func(program_uniform_4fv, "glProgramUniform4fv");
	core_load_func(program_uniform_4i, "glProgramUniform4i");
	core_load_func(program_uniform_4iv, "glProgramUniform4iv");
	core_load_func(program_uniform_4ui, "glProgramUniform4ui");
	core_load_func(program_uniform_4uiv, "glProgramUniform4uiv");
	core_load_func(program_uniform_matrix_2dv, "glProgramUniformMatrix2dv");
	core_load_func(program_uniform_matrix_2fv, "glProgramUniformMatrix2fv");
	core_load_func(program_uniform_matrix_2x3dv, "glProgramUniformMatrix2x3dv");
	core_load_func(program_uniform_matrix_2x3fv, "glProgramUniformMatrix2x3fv");
	core_load_func(program_uniform_matrix_2x4dv, "glProgramUniformMatrix2x4dv");
	core_load_func(program_uniform_matrix_2x4fv, "glProgramUniformMatrix2x4fv");
	core_load_func(program_uniform_matrix_3dv, "glProgramUniformMatrix3dv");
	core_load_func(program_uniform_matrix_3fv, "glProgramUniformMatrix3fv");
	core_load_func(program_uniform_matrix_3x2dv, "glProgramUniformMatrix3x2dv");
	core_load_func(program_uniform_matrix_3x2fv, "glProgramUniformMatrix3x2fv");
	core_load_func(program_uniform_matrix_3x4dv, "glProgramUniformMatrix3x4dv");
	core_load_func(program_uniform_matrix_3x4fv, "glProgramUniformMatrix3x4fv");
	core_load_func(program_uniform_matrix_4dv, "glProgramUniformMatrix4dv");
	core_load_func(program_uniform_matrix_4fv, "glProgramUniformMatrix4fv");
	core_load_func(program_uniform_matrix_4x2dv, "glProgramUniformMatrix4x2dv");
	core_load_func(program_uniform_matrix_4x2fv, "glProgramUniformMatrix4x2fv");
	core_load_func(program_uniform_matrix_4x3dv, "glProgramUniformMatrix4x3dv");
	core_load_func(program_uniform_matrix_4x3fv, "glProgramUniformMatrix4x3fv");
	core_load_func(release_shader_compiler, "glReleaseShaderCompiler");
	core_load_func(scissor_array_v, "glScissorArrayv");
	core_load_func(scissor_indexed, "glScissorIndexed");
	core_load_func(scissor_indexed_v, "glScissorIndexedv");
	core_load_func(shader_binary, "glShaderBinary");
	core_load_func(use_program_stages, "glUseProgramStages");
	core_load_func(validate_program_pipeline, "glValidateProgramPipeline");
	core_load_func(vertex_attrib_l1d, "glVertexAttribL1d");
	core_load_func(vertex_attrib_l1dv, "glVertexAttribL1dv");
	core_load_func(vertex_attrib_l2d, "glVertexAttribL2d");
	core_load_func(vertex_attrib_l2dv, "glVertexAttribL2dv");
	core_load_func(vertex_attrib_l3d, "glVertexAttribL3d");
	core_load_func(vertex_attrib_l3dv, "glVertexAttribL3dv");
	core_load_func(vertex_attrib_l4d, "glVertexAttribL4d");
	core_load_func(vertex_attrib_l4dv, "glVertexAttribL4dv");
	core_load_func(vertex_attrib_l_pointer, "glVertexAttribLPointer");
	core_load_func(viewport_array_v, "glViewportArrayv");
	core_load_func(viewport_indexed_f, "glViewportIndexedf");
	core_load_func(viewport_indexed_fv, "glViewportIndexedfv");
	return num_failed;
}

int load_gl_4_2_functions()
{
	int num_failed = load_gl_4_1_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(bind_image_texture, "glBindImageTexture");
	core_load_func(draw_arrays_instanced_base_instance, "glDrawArraysInstancedBaseInstance");
	core_load_func(draw_elements_instanced_base_instance, "glDrawElementsInstancedBaseInstance");
	core_load_func(draw_elements_instanced_base_vertex_base_instance, "glDrawElementsInstancedBaseVertexBaseInstance");
	core_load_func(draw_transform_feedback_instanced, "glDrawTransformFeedbackInstanced");
	core_load_func(draw_transform_feedback_stream_instanced, "glDrawTransformFeedbackStreamInstanced");
	core_load_func(get_active_atomic_counter_buffer_iv, "glGetActiveAtomicCounterBufferiv");
	core_load_func(get_internalformat_iv, "glGetInternalformativ");
	core_load_func(memory_barrier, "glMemoryBarrier");
	core_load_func(tex_storage_1d, "glTexStorage1D");
	core_load_func(tex_storage_2d, "glTexStorage2D");
	core_load_func(tex_storage_3d, "glTexStorage3D");
	return num_failed;
}

int load_gl_4_3_functions()
{
	int num_failed = load_gl_4_2_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(bind_vertex_buffer, "glBindVertexBuffer");
	core_load_func(clear_buffer_data, "glClearBufferData");
	core_load_func(clear_buffer_sub_data, "glClearBufferSubData");
	core_load_func(copy_image_sub_data, "glCopyImageSubData");
	core_load_func(debug_message_callback, "glDebugMessageCallback");
	core_load_func(debug_message_control, "glDebugMessageControl");
	core_load_func(debug_message_insert, "glDebugMessageInsert");
	core_load_func(dispatch_compute, "glDispatchCompute");
	core_load_func(dispatch_compute_indirect, "glDispatchComputeIndirect");
	core_load_func(framebuffer_parameter_i, "glFramebufferParameteri");
	core_load_func(get_debug_message_log, "glGetDebugMessageLog");
	core_load_func(get_framebuffer_parameter_iv, "glGetFramebufferParameteriv");
	core_load_func(get_internalformat_i64v, "glGetInternalformati64v");
	core_load_func(get_object_label, "glGetObjectLabel");
	core_load_func(get_object_ptr_label, "glGetObjectPtrLabel");
	core_load_func(get_program_interface_iv, "glGetProgramInterfaceiv");
	core_load_func(get_program_resource_index, "glGetProgramResourceIndex");
	core_load_func(get_program_resource_location, "glGetProgramResourceLocation");
	core_load_func(get_program_resource_location_index, "glGetProgramResourceLocationIndex");
	core_load_func(get_program_resource_name, "glGetProgramResourceName");
	core_load_func(get_program_resource_iv, "glGetProgramResourceiv");
	core_load_func(invalidate_buffer_data, "glInvalidateBufferData");
	core_load_func(invalidate_buffer_sub_data, "glInvalidateBufferSubData");
	core_load_func(invalidate_framebuffer, "glInvalidateFramebuffer");
	core_load_func(invalidate_sub_framebuffer, "glInvalidateSubFramebuffer");
	core_load_func(invalidate_tex_image, "glInvalidateTexImage");
	core_load_func(invalidate_tex_sub_image, "glInvalidateTexSubImage");
	core_load_func(multi_draw_arrays_indirect, "glMultiDrawArraysIndirect");
	core_load_func(multi_draw_elements_indirect, "glMultiDrawElementsIndirect");
	core_load_func(object_label, "glObjectLabel");
	core_load_func(object_ptr_label, "glObjectPtrLabel");
	core_load_func(pop_debug_group, "glPopDebugGroup");
	core_load_func(push_debug_group, "glPushDebugGroup");
	core_load_func(shader_storage_block_binding, "glShaderStorageBlockBinding");
	core_load_func(tex_buffer_range, "glTexBufferRange");
	core_load_func(tex_storage_2d_multisample, "glTexStorage2DMultisample");
	core_load_func(tex_storage_3d_multisample, "glTexStorage3DMultisample");
	core_load_func(texture_view, "glTextureView");
	core_load_func(vertex_attrib_binding, "glVertexAttribBinding");
	core_load_func(vertex_attrib_format, "glVertexAttribFormat");
	core_load_func(vertex_attrib_i_format, "glVertexAttribIFormat");
	core_load_func(vertex_attrib_l_format, "glVertexAttribLFormat");
	core_load_func(vertex_binding_divisor, "glVertexBindingDivisor");
	return num_failed;
}

int load_gl_4_4_functions()
{
	int num_failed = load_gl_4_3_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(bind_buffers_base, "glBindBuffersBase");
	core_load_func(bind_buffers_range, "glBindBuffersRange");
	core_load_func(bind_image_textures, "glBindImageTextures");
	core_load_func(bind_samplers, "glBindSamplers");
	core_load_func(bind_textures, "glBindTextures");
	core_load_func(bind_vertex_buffers, "glBindVertexBuffers");
	core_load_func(buffer_storage, "glBufferStorage");
	core_load_func(clear_tex_image, "glClearTexImage");
	core_load_func(clear_tex_sub_image, "glClearTexSubImage");
	return num_failed;
}

int load_gl_4_5_functions()
{
	int num_failed = load_gl_4_4_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(bind_texture_unit, "glBindTextureUnit");
	core_load_func(blit_named_framebuffer, "glBlitNamedFramebuffer");
	core_load_func(check_named_framebuffer_status, "glCheckNamedFramebufferStatus");
	core_load_func(clear_named_buffer_data, "glClearNamedBufferData");
	core_load_func(clear_named_buffer_sub_data, "glClearNamedBufferSubData");
	core_load_func(clear_named_framebuffer_fi, "glClearNamedFramebufferfi");
	core_load_func(clear_named_framebuffer_fv, "glClearNamedFramebufferfv");
	core_load_func(clear_named_framebuffer_iv, "glClearNamedFramebufferiv");
	core_load_func(clear_named_framebuffer_uiv, "glClearNamedFramebufferuiv");
	core_load_func(clip_control, "glClipControl");
	core_load_func(compressed_texture_sub_image_1d, "glCompressedTextureSubImage1D");
	core_load_func(compressed_texture_sub_image_2d, "glCompressedTextureSubImage2D");
	core_load_func(compressed_texture_sub_image_3d, "glCompressedTextureSubImage3D");
	core_load_func(copy_named_buffer_sub_data, "glCopyNamedBufferSubData");
	core_load_func(copy_texture_sub_image_1d, "glCopyTextureSubImage1D");
	core_load_func(copy_texture_sub_image_2d, "glCopyTextureSubImage2D");
	core_load_func(copy_texture_sub_image_3d, "glCopyTextureSubImage3D");
	core_load_func(create_buffers, "glCreateBuffers");
	core_load_func(create_framebuffers, "glCreateFramebuffers");
	core_load_func(create_program_pipelines, "glCreateProgramPipelines");
	core_load_func(create_queries, "glCreateQueries");
	core_load_func(create_renderbuffers, "glCreateRenderbuffers");
	core_load_func(create_samplers, "glCreateSamplers");
	core_load_func(create_textures, "glCreateTextures");
	core_load_func(create_transform_feedbacks, "glCreateTransformFeedbacks");
	core_load_func(create_vertex_arrays, "glCreateVertexArrays");
	core_load_func(disable_vertex_array_attrib, "glDisableVertexArrayAttrib");
	core_load_func(enable_vertex_array_attrib, "glEnableVertexArrayAttrib");
	core_load_func(flush_mapped_named_buffer_range, "glFlushMappedNamedBufferRange");
	core_load_func(generate_texture_mipmap, "glGenerateTextureMipmap");
	core_load_func(get_compressed_texture_image, "glGetCompressedTextureImage");
	core_load_func(get_compressed_texture_sub_image, "glGetCompressedTextureSubImage");
	core_load_func(get_graphics_reset_status, "glGetGraphicsResetStatus");
	core_load_func(get_named_buffer_parameter_i64v, "glGetNamedBufferParameteri64v");
	core_load_func(get_named_buffer_parameter_iv, "glGetNamedBufferParameteriv");
	core_load_func(get_named_buffer_pointer_v, "glGetNamedBufferPointerv");
	core_load_func(get_named_buffer_sub_data, "glGetNamedBufferSubData");
	core_load_func(get_named_framebuffer_attachment_parameter_iv, "glGetNamedFramebufferAttachmentParameteriv");
	core_load_func(get_named_framebuffer_parameter_iv, "glGetNamedFramebufferParameteriv");
	core_load_func(get_named_renderbuffer_parameter_iv, "glGetNamedRenderbufferParameteriv");
	core_load_func(get_query_buffer_object_i64v, "glGetQueryBufferObjecti64v");
	core_load_func(get_query_buffer_object_iv, "glGetQueryBufferObjectiv");
	core_load_func(get_query_buffer_object_ui64v, "glGetQueryBufferObjectui64v");
	core_load_func(get_query_buffer_object_uiv, "glGetQueryBufferObjectuiv");
	core_load_func(get_texture_image, "glGetTextureImage");
	core_load_func(get_texture_level_parameter_fv, "glGetTextureLevelParameterfv");
	core_load_func(get_texture_level_parameter_iv, "glGetTextureLevelParameteriv");
	core_load_func(get_texture_parameter_i_iv, "glGetTextureParameterIiv");
	core_load_func(get_texture_parameter_i_uiv, "glGetTextureParameterIuiv");
	core_load_func(get_texture_parameter_fv, "glGetTextureParameterfv");
	core_load_func(get_texture_parameter_iv, "glGetTextureParameteriv");
	core_load_func(get_texture_sub_image, "glGetTextureSubImage");
	core_load_func(get_transform_feedback_i64v, "glGetTransformFeedbacki64_v");
	core_load_func(get_transform_feedback_i_v, "glGetTransformFeedbacki_v");
	core_load_func(get_transform_feedback_iv, "glGetTransformFeedbackiv");
	core_load_func(get_vertex_array_indexed_64iv, "glGetVertexArrayIndexed64iv");
	core_load_func(get_vertex_array_indexed_iv, "glGetVertexArrayIndexediv");
	core_load_func(get_vertex_array_iv, "glGetVertexArrayiv");
	core_load_func(getn_compressed_tex_image, "glGetnCompressedTexImage");
	core_load_func(getn_tex_image, "glGetnTexImage");
	core_load_func(getn_uniform_dv, "glGetnUniformdv");
	core_load_func(getn_uniform_fv, "glGetnUniformfv");
	core_load_func(getn_uniform_iv, "glGetnUniformiv");
	core_load_func(getn_uniform_uiv, "glGetnUniformuiv");
	core_load_func(invalidate_named_framebuffer_data, "glInvalidateNamedFramebufferData");
	core_load_func(invalidate_named_framebuffer_sub_data, "glInvalidateNamedFramebufferSubData");
	core_load_func(map_named_buffer, "glMapNamedBuffer");
	core_load_func(map_named_buffer_range, "glMapNamedBufferRange");
	core_load_func(memory_barrier_by_region, "glMemoryBarrierByRegion");
	core_load_func(named_buffer_data, "glNamedBufferData");
	core_load_func(named_buffer_storage, "glNamedBufferStorage");
	core_load_func(named_buffer_sub_data, "glNamedBufferSubData");
	core_load_func(named_framebuffer_draw_buffer, "glNamedFramebufferDrawBuffer");
	core_load_func(named_framebuffer_draw_buffers, "glNamedFramebufferDrawBuffers");
	core_load_func(named_framebuffer_parameter_i, "glNamedFramebufferParameteri");
	core_load_func(named_framebuffer_read_buffer, "glNamedFramebufferReadBuffer");
	core_load_func(named_framebuffer_renderbuffer, "glNamedFramebufferRenderbuffer");
	core_load_func(named_framebuffer_texture, "glNamedFramebufferTexture");
	core_load_func(named_framebuffer_texture_layer, "glNamedFramebufferTextureLayer");
	core_load_func(named_renderbuffer_storage, "glNamedRenderbufferStorage");
	core_load_func(named_renderbuffer_storage_multisample, "glNamedRenderbufferStorageMultisample");
	core_load_func(read_n_pixels, "glReadnPixels");
	core_load_func(texture_barrier, "glTextureBarrier");
	core_load_func(texture_buffer, "glTextureBuffer");
	core_load_func(texture_buffer_range, "glTextureBufferRange");
	core_load_func(texture_parameter_i_iv, "glTextureParameterIiv");
	core_load_func(texture_parameter_i_uiv, "glTextureParameterIuiv");
	core_load_func(texture_parameter_f, "glTextureParameterf");
	core_load_func(texture_parameter_fv, "glTextureParameterfv");
	core_load_func(texture_parameter_i, "glTextureParameteri");
	core_load_func(texture_parameter_iv, "glTextureParameteriv");
	core_load_func(texture_storage_1d, "glTextureStorage1D");
	core_load_func(texture_storage_2d, "glTextureStorage2D");
	core_load_func(texture_storage_2d_multisample, "glTextureStorage2DMultisample");
	core_load_func(texture_storage_3d, "glTextureStorage3D");
	core_load_func(texture_storage_3d_multisample, "glTextureStorage3DMultisample");
	core_load_func(texture_sub_image_1d, "glTextureSubImage1D");
	core_load_func(texture_sub_image_2d, "glTextureSubImage2D");
	core_load_func(texture_sub_image_3d, "glTextureSubImage3D");
	core_load_func(transform_feedback_buffer_base, "glTransformFeedbackBufferBase");
	core_load_func(transform_feedback_buffer_range, "glTransformFeedbackBufferRange");
	core_load_func(unmap_named_buffer, "glUnmapNamedBuffer");
	core_load_func(vertex_array_attrib_binding, "glVertexArrayAttribBinding");
	core_load_func(vertex_array_attrib_format, "glVertexArrayAttribFormat");
	core_load_func(vertex_array_attrib_i_format, "glVertexArrayAttribIFormat");
	core_load_func(vertex_array_attrib_l_format, "glVertexArrayAttribLFormat");
	core_load_func(vertex_array_binding_divisor, "glVertexArrayBindingDivisor");
	core_load_func(vertex_array_element_buffer, "glVertexArrayElementBuffer");
	core_load_func(vertex_array_vertex_buffer, "glVertexArrayVertexBuffer");
	core_load_func(vertex_array_vertex_buffers, "glVertexArrayVertexBuffers");
	return num_failed;
}

int load_gl_4_6_functions()
{
	int num_failed = load_gl_4_5_functions();
	auto core_load_func = [&] (auto& func, char const* spec) {
		get_proc(func, spec);
		if (!func) ++num_failed;
	};
	core_load_func(multi_draw_arrays_indirect_count, "glMultiDrawArraysIndirectCount");
	core_load_func(multi_draw_elements_indirect_count, "glMultiDrawElementsIndirectCount");
	core_load_func(polygon_offset_clamp, "glPolygonOffsetClamp");
	core_load_func(specialize_shader, "glSpecializeShader");
	return num_failed;
}


} //namespace

namespace sys {
namespace {
using load_extension_ptr = int(*)();
struct map_entry {
	string_view ext_name;
	ext::load_result* ext_variable;
	load_extension_ptr loaderFunc = nullptr;
};

bool operator<(map_entry const& a, map_entry const& b)
{
	return a.ext_name < b.ext_name;
}

bool operator==(map_entry const& a, map_entry const& b)
{
	return a.ext_name == b.ext_name;
}

[[nodiscard]] std::vector<map_entry> initialize_mapping_table()
{
	std::vector<map_entry> table(0);
	// generated code goes here
	std::sort(begin(table), end(table));
	return table;
}

void clear_extension_vars()
{
}

void load_extension(std::vector<map_entry>& table, string_view extension)
{
	auto compare = [] (map_entry const& e, string_view a)
	{
		return a == e.ext_name;
	};
	auto entry = aw::binary_find(begin(table), end(table), extension, compare);
	
	if (entry != end(table)) {
		const auto loader = entry->loaderFunc;
		const int  num_failed = loader ? loader() : 0;
		(*entry->ext_variable) = ext::load_result(true, num_failed);
	}
}


static void load_extensions(std::vector<map_entry> &table)
{
	GLint idx;
	GLint num = 0;
	gl::get_integer_v(GL_NUM_EXTENSIONS, &num);

	for(idx = 0; idx < num; ++idx) {
		const auto extension_name = reinterpret_cast<const char*>(gl::get_string_i(GL_EXTENSIONS, idx));
		load_extension(table, extension_name);
	}
}

ext::load_result load_functions_ext()
{
	clear_extension_vars();
	
	get_proc(get_integer_v, "glGetIntegerv");
	if(!get_integer_v) return ext::load_result(false, 1);
	get_proc(get_string_i, "glGetStringi");
	if(!get_string_i) return ext::load_result(false, 1);
	
	std::vector<map_entry> table = initialize_mapping_table();
	load_extensions(table);
	return ext::load_result(true, 0);
}
} //namespace

ext::load_result load_functions_3_2()
{
	load_functions_ext();

	int num_failed = load_gl_3_2_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_3_3()
{
	load_functions_ext();

	int num_failed = load_gl_3_3_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_0()
{
	load_functions_ext();

	int num_failed = load_gl_4_0_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_1()
{
	load_functions_ext();

	int num_failed = load_gl_4_1_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_2()
{
	load_functions_ext();

	int num_failed = load_gl_4_2_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_3()
{
	load_functions_ext();

	int num_failed = load_gl_4_3_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_4()
{
	load_functions_ext();

	int num_failed = load_gl_4_4_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_5()
{
	load_functions_ext();

	int num_failed = load_gl_4_5_functions();
	return ext::load_result(true, num_failed);
}

ext::load_result load_functions_4_6()
{
	load_functions_ext();

	int num_failed = load_gl_4_6_functions();
	return ext::load_result(true, num_failed);
}

static int g_major_version = 0;
static int g_minor_version = 0;

static void get_gl_version()
{
	get_integer_v(GL_MAJOR_VERSION, &g_major_version);
	get_integer_v(GL_MINOR_VERSION, &g_minor_version);
}

int get_major_version()
{
	if(g_major_version == 0)
		get_gl_version();
	return g_major_version;
}

int get_minor_version()
{
	//Yes, check the major version to get the minor one.
	if(g_major_version == 0)
		get_gl_version();
	return g_minor_version;
}

// TODO: add version class
bool is_version_geq(int majorVersion, int minorVersion)
{
	if(g_major_version == 0)
		get_gl_version();
	
	if(majorVersion < g_major_version) return true;
	if(majorVersion > g_major_version) return false;
	if(minorVersion <= g_minor_version) return true;
	return false;
}

} //namespace sys
} //namespace gl
