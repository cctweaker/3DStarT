Import("env")

my_flags = env.ParseFlags(env['BUILD_FLAGS'])
defines = {k: v for (k, v) in my_flags.get("CPPDEFINES")}
print(defines)

env.Replace(PROGNAME="3DStarT_v%s" % (defines.get("VERSION") or "0beta"))
