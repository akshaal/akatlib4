import akat_write_cflags

START_REG_N = 16
START_LOW_REG_N = 2

defined_static_vars = []
configured_as_reg = {}
reg_to_var = {}
used_reg = {}
next_reg_n = START_REG_N
next_low_reg_n = START_LOW_REG_N
initials = {}

def configure_as_reg(v, low = False):
    """Call me and I will configure your variable 'v' to be a hardware register."""

    global next_reg_n
    global next_low_reg_n

    if low:
        reg = "r" + str(next_low_reg_n)
        next_low_reg_n += 1
    else:
        reg = "r" + str(next_reg_n)
        next_reg_n += 1

    configured_as_reg[v] = reg
    reg_to_var[reg] = v

    akat_write_cflags.add("-ffixed-" + reg)

    return reg

configure_as_reg("__akat_one__", low = True)

# =================================================================================
# Implementation of macro

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["decl"],
                           required_enclosing_macros = ["GLOBAL"],
                           optional_kvs = { "initial": "0"},
                           keywords = ["ignore_dups"])

        t, name = ctx.decl.rsplit(" ", 1)

        scope_m = akat.get_enclosing_macro_or_none("SCOPE")

        ns = akat.get_current_namespace()
        full_name = akat.add_namespace(name)

        # Avoid duplicated definitions + we do some summary at the end
        already_defined = full_name in defined_static_vars

        if already_defined:
            if not ignore_dups:
                akat.fatal_error(STRESS(name), " is already defined (", ns, ")")
        else:
            initials[full_name] = ctx.initial
            defined_static_vars.append(full_name)

            if full_name in configured_as_reg:
                reg = configured_as_reg[full_name]
                used_reg[full_name] = reg
                mod = "register"
                attr = " asm (\"" + reg + "\")"
            else:
                mod = "static"
                attr = " = " + ctx.initial

            ctx.GLOBAL.add_global_code(mod +" " + t + " "  + full_name + attr + ";")

        if scope_m != None:
            scope_m.map_as(full_name, name, ignore_dups = ctx.ignore_dups)

        return "";

    def postvalidate():
        if len(defined_static_vars) > 0 or len(configured_as_reg) > 0:
            akat.print_sep()
            akat.print_info("Defined static vars:")

        for v in defined_static_vars:
            extra = ""
            if v in used_reg:
                extra = used_reg[v]

            akat.print_info("    ", STRESS_COLOR, v, "   ", RESET_COLOR, extra)

        # Unused regs
        shown_unused_header = False
        for v in configured_as_reg:
            if v not in used_reg:
                if not shown_unused_header:
                    akat.print_sep()
                    akat.print_error("Following static variables are configured to use registers. But we can't find such static variables! Are you sure your USE_REG$ goes BEFORE parts that declare the variable?..")
                    shown_unused_header = True

                akat.print_error("    ", STRESS_COLOR, v)

        if shown_unused_header:
            akat.fatal_error("Please fix it!")
