class Macro:
    def __init__(self):
        self.__mappings = {}
        self.__parent_scope = akat.get_enclosing_macro_or_none("SCOPE", skip_top = 0)

    def map_as(self, global_name, local_name, ignore_dups = False):
        if not ignore_dups and self.__is_already_mapped(local_name):
            akat.fatal_error("Variable with name ", STRESS(local_name), " is already defined as ", STRESS(self.__mappings[local_name]))

        if global_name != local_name:
            self.__mappings[local_name] = global_name

    def __is_already_mapped(self, local_name):
        return local_name in self.__mappings

    def __get_all_mappings(self):
        m = {}

        if self.__parent_scope != None:
            parent_m = self.__parent_scope.__get_all_mappings()
            m.update(parent_m)

        m.update(self.__mappings)

        return m

    def __get_pre_body_defs(self):
        m = self.__get_all_mappings()
        return ["#define " + local_name + " " + m[local_name] for local_name in sorted(m)]

    def __get_post_body_defs(self):
        m = self.__get_all_mappings()

        res = ["#undef " + local_name for local_name in sorted(m)]
        if self.__restore and self.__parent_scope != None:
            res += self.__parent_scope.__get_pre_body_defs()

        return res

    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], keywords = ["restore"], allow_nesting = True, body = True)
        self.__restore = ctx.restore

        def code_in_namespace():
            rendered_body = akat.transform(inv.body)

            render_context = {
                "pre_body_defs": self.__get_pre_body_defs(),
                "post_body_defs": self.__get_post_body_defs(),
                "rendered_body": rendered_body
            }

            return akat.transform(akat.render(self, **render_context))

        return akat.run_with_namespace(code_in_namespace, ctx.name, "scope")
