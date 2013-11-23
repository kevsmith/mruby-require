#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"


#include <stdlib.h>
#include <sys/stat.h>

#define E_LOAD_ERROR (mrb_class_get(mrb, "LoadError"))

static mrb_value
mrb_require_load_rb_str(mrb_state *mrb, mrb_value self)
{
  mrb_value code = mrb_nil_value();

  mrb_get_args(mrb, "S", &code);

  return mrb_load_nstring(mrb, mrb_string_value_cstr(mrb, &code), RSTRING_LEN(code));

}

static mrb_value
mrb_require_load_mrb_file(mrb_state *mrb, mrb_value self)
{
  char *path_ptr = NULL;
  FILE *fp = NULL;
  mrb_value path;
  mrb_value result;

  mrb_get_args(mrb, "S", &path);
  path_ptr = mrb_str_to_cstr(mrb, path);

  fp = fopen(path_ptr, "rb");
  if (fp == NULL) {
    mrb_raisef(mrb, E_LOAD_ERROR, "can't open file -- %S", path);
  }

  result = mrb_load_file(mrb, fp);
  fclose(fp);
  return result;
}

void
mrb_mruby_require_gem_init(mrb_state *mrb)
{
  struct RClass *krn;
  krn = mrb->kernel_module;

  mrb_define_method(mrb, krn, "_load_rb_str",   mrb_require_load_rb_str,   MRB_ARGS_ANY());
  mrb_define_method(mrb, krn, "_load_mrb_file", mrb_require_load_mrb_file, MRB_ARGS_REQ(1));
}

void
mrb_mruby_require_gem_final(mrb_state *mrb)
{
}
