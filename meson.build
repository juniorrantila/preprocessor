project('preprocessor', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'cpp_eh=none',
    'cpp_rtti=false',
    'default_library=static',
    'warning_level=3',
    'buildtype=release'
  ])

add_global_arguments('-Wno-c99-designator', language: 'cpp')
add_global_arguments('-Wno-c99-extensions', language: 'cpp')
add_global_arguments('-Wno-gnu-zero-variadic-macro-arguments', language: 'cpp')
add_global_arguments('-Wno-keyword-macro', language: 'cpp')
add_global_arguments('-Wno-gnu-conditional-omitted-operand', language: 'cpp')
add_global_arguments('-Wno-format-pedantic', language: 'cpp')
add_global_arguments('-Wno-nullability-extension', language: 'cpp')
add_global_arguments('-Wno-gnu-statement-expression', language: 'cpp')
add_global_arguments('-Wno-gnu-anonymous-struct', language: 'cpp')
add_global_arguments('-Wno-c++2b-extensions', language: 'cpp')

add_global_arguments('-fdebug-prefix-map=../=', language: 'cpp')
add_global_arguments('-ffile-prefix-map=../=', language: 'cpp')

libJR_proj = subproject('LibJR')
libJR_dep = libJR_proj.get_variable('libJR_dep')
libCore_dep = libJR_proj.get_variable('libCore_dep')
libMain_dep = libJR_proj.get_variable('libMain_dep')

executable('preprocessor', [
    'src/main.cpp'
  ],
  dependencies: [
    libCore_dep,
    libJR_dep,
    libMain_dep,
  ])
