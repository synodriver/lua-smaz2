#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"

#include "smaz2.h"

#if defined(_WIN32) || defined(_WIN64)
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */


static int
lcompress(lua_State *L)
{
    int stack_size = lua_gettop(L);
    char *input;
    size_t input_size = 0;
    input = (char *) luaL_checklstring(L, 1, &input_size);
    size_t output_size = input_size;
    if (stack_size == 2) // 额外输入了output_size
    {
        output_size = (size_t) luaL_checkinteger(L, 2);
    }
    else if (stack_size > 2)
    {
        return luaL_error(L, "2 args at most, data and output size which is optional");
    }
    unsigned char *output_buf = (unsigned char *) lua_newuserdata(L, output_size);
    unsigned long buffer_updated = smaz2_compress(output_buf, (unsigned long)output_size, (unsigned char *)input, (unsigned long)input_size);
//    if (buffer_updated == (unsigned long) (output_size + 1))
//    {
//        return luaL_error(L, "output buffer is too small");
//    }
    lua_pushlstring(L, (const char*)output_buf, (size_t) buffer_updated);
    return 1;
}

static int
ldecompress(lua_State *L)
{
    int stack_size = lua_gettop(L);
    char *input;
    size_t input_size = 0;
    input = (char *) luaL_checklstring(L, 1, &input_size);
    size_t output_size = input_size * 2;
    if (stack_size == 2) // 额外输入了output_size
    {
        output_size = (size_t) luaL_checkinteger(L, 2);
    }
    else if (stack_size > 2)
    {
        return luaL_error(L, "2 args at most, data and output size which is optional");
    }
    unsigned char *output_buf = (unsigned char *) lua_newuserdata(L, output_size);
    unsigned long buffer_updated = smaz2_decompress(output_buf, (unsigned long)output_size, (unsigned char *)input, (unsigned long)input_size);
//    if (buffer_updated == (int) (output_size + 1))
//    {
//        return luaL_error(L, "output buffer is too small");
//    }
    lua_pushlstring(L, (const char*)output_buf, (size_t) buffer_updated);
    return 1;
}

static luaL_Reg lua_funcs[] = {
        {"compress",   &lcompress},
        {"decompress", &ldecompress},
        {NULL, NULL}
};

DLLEXPORT int luaopen_smaz2(lua_State *L)
{
    luaL_newlib(L, lua_funcs);
    return 1;
}