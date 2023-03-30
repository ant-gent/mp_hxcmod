// Include MicroPython API.
#include "py/runtime.h"

#include "hxcmod.h"

typedef struct _hxcmod_Hxcmod_obj_t {
    mp_obj_base_t base;
    modcontext *modctx;
} hxcmod_Hxcmod_obj_t;

STATIC mp_obj_t hxcmod_Hxcmod_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t* args){

    hxcmod_Hxcmod_obj_t *self = mp_obj_malloc(hxcmod_Hxcmod_obj_t, type);
    self->modctx = m_malloc(sizeof(modcontext));
    hxcmod_init(self->modctx);
    return MP_OBJ_FROM_PTR(self);
}

STATIC mp_obj_t hxcmod_Hxcmod_load(mp_obj_t self_in, mp_obj_t buffer){

    hxcmod_Hxcmod_obj_t *self = MP_OBJ_TO_PTR(self_in);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buffer, &bufinfo, MP_BUFFER_READ);

    int result = hxcmod_load(self->modctx, bufinfo.buf, bufinfo.len);
    
    return mp_obj_new_int(result);

}

MP_DEFINE_CONST_FUN_OBJ_2(hxcmod_Hxcmod_load_obj, hxcmod_Hxcmod_load);

STATIC mp_obj_t hxcmod_Hxcmod_fillbuffer(mp_obj_t self_in, mp_obj_t buffer){

    hxcmod_Hxcmod_obj_t *self = MP_OBJ_TO_PTR(self_in);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buffer, &bufinfo, MP_BUFFER_WRITE);

    hxcmod_fillbuffer(self->modctx, bufinfo.buf, bufinfo.len / 4, NULL);

    return mp_const_none;

}

MP_DEFINE_CONST_FUN_OBJ_2(hxcmod_Hxcmod_fillbuffer_obj, hxcmod_Hxcmod_fillbuffer);


STATIC const mp_rom_map_elem_t hxcmod_Hxcmod_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_load), MP_ROM_PTR(&hxcmod_Hxcmod_load_obj) },
    { MP_ROM_QSTR(MP_QSTR_fillbuffer), MP_ROM_PTR(&hxcmod_Hxcmod_fillbuffer_obj) }
};
STATIC MP_DEFINE_CONST_DICT(hxcmod_Hxcmod_locals_dict, hxcmod_Hxcmod_locals_dict_table);

// This defines the type(Hxcmod) object.
MP_DEFINE_CONST_OBJ_TYPE(
    hxcmod_type_Hxcmod,
    MP_QSTR_Hxcmod,
    MP_TYPE_FLAG_NONE,
    make_new, hxcmod_Hxcmod_make_new,
    locals_dict, &hxcmod_Hxcmod_locals_dict
    );

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t hxcmod_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_hxcmod) },
    { MP_ROM_QSTR(MP_QSTR_Hxcmod),    MP_ROM_PTR(&hxcmod_type_Hxcmod) },
};
STATIC MP_DEFINE_CONST_DICT(hxcmod_module_globals, hxcmod_module_globals_table);

// Define module object.
const mp_obj_module_t hxcmod_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&hxcmod_module_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_hxcmod, hxcmod_module);
