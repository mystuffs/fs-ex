#include <napi.h>
#include <iostream>
#include <fstream>
#include <string>

Napi::String version(const Napi::CallbackInfo& args)
{
    return Napi::String::New(args.Env(), "0.1");
}

Napi::String read_file(const Napi::CallbackInfo& args)
{
    std::ifstream ifs;
    std::string value;
    std::string line;
    ifs.open(args[0].As<Napi::String>());

    if (!ifs.good())
    {
        return Napi::String::New(args.Env(), "");
    }
    while (std::getline(ifs, line))
    {
        value += line + '\n';
    }
    ifs.close();
    return Napi::String::New(args.Env(), value);
}

Napi::Boolean append_file(const Napi::CallbackInfo& args)
{
    std::ofstream ofs;
    bool ret;
    ofs.open(args[0].As<Napi::String>(), std::ios_base::app);
    if (ofs.is_open())
    {
        ofs << args[1].As<Napi::String>(); // pointer? wait what
    }
    return Napi::Boolean::New(args.Env(), ret == 0);
}

Napi::Object InitFSEx(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "readFile"),
        Napi::Function::New(env, read_file)
    );
    exports.Set(
        Napi::String::New(env, "version"),
        Napi::Function::New(env, version)
    );
    exports.Set(
        Napi::String::New(env, "appendFile"),
        Napi::Function::New(env, append_file)
    );
    return exports;
}

NODE_API_MODULE(version, InitFSEx);
