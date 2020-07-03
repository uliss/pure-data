# -*- coding: utf-8 -*-

class CppExternal(object):
    def __init__(self, module, name, include_headers=None):
        # default arguments
        if include_headers is None:
            include_headers = []

        self.module = module
        self.name = name
        self.class_ = self.module.title() + self.name.title();
        self.include_headers = include_headers

    def generate(self, methods='common'):
        self.generate_header()
        self.generate_class_begin()
        self.generate_methods(methods)
        self.generate_class_end()
        self.generate_setup()

    def generate_methods(self, methods):
        if isinstance(methods, basestring):
            if methods == 'all':
                methods = ['bang', 'float', 'symbol', 'list', 'anything']
            elif methods == 'common':
                methods = ['bang', 'float', 'symbol', 'list']
            elif methods == '':
                methods = ['bang', 'float']

        methods.sort()

        for m in methods:
            try:
                func = getattr(self, 'generate_' + m)

                code_attr_name = 'code_' + m;
                if hasattr(self, code_attr_name):
                    func(code=getattr(self, code_attr_name))
                else:
                    func()

            except AttributeError:
                print m, " not found"

    def generate_header(self):
        print "/// this file is autogenerated, do not edit!"
        for f in self.include_headers:
            print "#include <{}>".format(f)

        print '''
#include "ceammc_factory.h"
#include "ceammc_object.h"

using namespace ceammc;
        '''

    def generate_class_begin(self):
        res = '''
class {0} : public BaseObject
{{
    using FloatUnaryFn = t_float(*)(t_float);
public:
    {0}(const PdArgs& a) : BaseObject(a)
    {{
        createOutlet();
    }}'''

        print res.format(self.class_)

    def generate_class_end(self):
        print '''
};
'''

    def generate_bang(self, code=''):
        res = '''
    void onBang() final
    {{
        {code}
    }}'''

        print res.format(code=code)

    def generate_float(self, code=''):
        res = '''
    void onFloat(t_float f) final
    {{
        {code}
    }}'''

        print res.format(code=code)

    def generate_list(self, code=''):
        res = '''
    void onList(const AtomList& l) final
    {{
        {code}
    }}'''
        print res.format(code=code)

    def generate_symbol(self, code=''):
        res = '''
    void onSymbol(t_symbol* s) final
    {{
        {code}
    }}'''
        print res.format(code=code)

    def generate_anything(self, code=''):
        res = '''
    void onAny(t_symbol* sel, const AtomList& l) final
    {{
        {code}
    }}'''

        print res.format(code=code)

    def str_setup(self, n=0):
        return  'ObjectFactory<{class_}> obj{n}("{mod}.{name}");'.format(class_=self.class_, mod=self.module, name=self.name, n=n)

    def generate_setup(self, methods=None):
        print '''
void setup_{0}_{1}()\n{{
    {2}
    }}'''.format(self.module, self.name, self.str_setup())


class CppSoundExternal(object):
    def __init__(self, module, name, include_headers=None, func_name=None):
        # default arguments
        if include_headers is None:
            include_headers = []

        self.module = module
        self.name = name
        self.func_name = func_name
        self.class_ = self.module.title() + self.name.title() + "Tilde";
        self.include_headers = include_headers

    def generate(self, methods='common'):
        self.generate_header()
        self.generate_class_begin()
        self.generate_class_end()
        self.generate_setup()

    def generate_header(self):
        print "/// this file is autogenerated, do not edit!"
        for f in self.include_headers:
            print "#include <{}>".format(f)

        print '''
#include "ceammc_factory.h"
#include "ceammc_soundobject.h"

using namespace ceammc;
        '''

    def generate_class_begin(self):
        res = '''
class {0} : public SoundExternal
{{
public:
    {0}(const PdArgs& a) : SoundExternal(a)
    {{
        createSignalOutlet();
    }}

    void processBlock(const t_sample** in, t_sample** out) final
    {{
        const auto BS = blockSize();
        for(size_t i = 0; i < BS; i += 8) {{
            out[0][i+0] = std::{1}(in[0][i+0]);
            out[0][i+1] = std::{1}(in[0][i+1]);
            out[0][i+2] = std::{1}(in[0][i+2]);
            out[0][i+3] = std::{1}(in[0][i+3]);
            out[0][i+4] = std::{1}(in[0][i+4]);
            out[0][i+5] = std::{1}(in[0][i+5]);
            out[0][i+6] = std::{1}(in[0][i+6]);
            out[0][i+7] = std::{1}(in[0][i+7]);
        }}
    }}'''

        print res.format(self.class_, self.func_name)

    def generate_class_end(self):
        print '''};
'''

    def str_setup(self, n=0):
        return 'SoundExternalFactory<{class_}> obj{n}("{mod}.{ext}~");'.format(class_=self.class_, mod=self.module, ext=self.name, n=n)

    def generate_setup(self):
        print '''
void setup_{mod}_{name}_tilde() {{
    {body}
}}
        '''.format(name=self.name, mod=self.module, body=self.str_setup());


class MathUnaryCppExternal(CppExternal):
    def __init__(self, name, func_name=None, headers=None):
        if headers is None:
            headers = ["cmath"]

        super(self.__class__, self).__init__("math", name, headers)

        self.func_name = func_name
        setattr(self, 'code_float', "floatTo(0, std::{0}(f));".format(func_name));
        setattr(self, 'code_list', "listTo(0, l.mapFloat(static_cast<FloatUnaryFn>(std::{0})));".format(func_name));


class MathUnaryCppExternalTilde(CppSoundExternal):
    def __init__(self, name, func_name=None, headers=None):
        if headers is None:
            headers = ["cmath"]

        super(self.__class__, self).__init__("math", name, headers, func_name=func_name)


class MathUnaryCppExternalBoth:
    def __init__(self, name, func_name=None, include_headers=None):
        if include_headers is None:
            include_headers = ["cmath"]

        self.name = name
        self.include_headers = include_headers
        self.ctl_ext = MathUnaryCppExternal(name, func_name, include_headers)
        self.snd_ext = MathUnaryCppExternalTilde(name, func_name, include_headers)

    def generate(self, methods=None):
        self.generate_header()
        self.ctl_ext.generate_class_begin()
        self.ctl_ext.generate_methods(methods)
        self.ctl_ext.generate_class_end()

        self.snd_ext.generate_class_begin()
        self.snd_ext.generate_class_end()
        self.generate_setup()

    def generate_header(self):
        print "/// this file is autogenerated, do not edit!"
        for f in self.include_headers:
            print "#include <{}>".format(f)

        print '''
#include "ceammc_factory.h"
#include "ceammc_object.h"
#include "ceammc_sound_external.h"

using namespace ceammc;
        '''

    def generate_setup(self):
        print '''
void setup_math_{name}() {{
    {mod0}
    {mod1}
}}
        '''.format(name=self.name, mod0=self.ctl_ext.str_setup(0), mod1=self.snd_ext.str_setup(1))
