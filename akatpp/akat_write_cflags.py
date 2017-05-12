import codecs

values = []

def add(val):
    values.append(val)

class Macro:
    def __init__(self):
        self.__ofile = None

    def render(self, inv):
        akat.require_no_body(inv)
        global ofile

        ofile = akat.require_arg(inv, 0, "First argument of the macro is the output file name relative to the current file.");
        akat.require_args(inv, 1)

        return ""

    def postvalidate():
        if len(values) == 0 and ofile == None:
            return

        if ofile == None:
            akat.fatal_error("This build requires special options to be used during compilation. Please use WRITE_CFLAGS$ macro to write such option into a file.")

        content = " ".join(values) + "\n"

        f = akat.get_current_directory() + "/" + ofile + ".cflags"
        akat.print_info("Writing ", STRESS_COLOR, f)

        codecs.open(f, "w", "utf-8").write(content)

