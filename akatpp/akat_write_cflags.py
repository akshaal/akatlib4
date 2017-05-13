import codecs

values = []

def add(val):
    values.append(val)

class Macro:
    def __init__(self):
        self.__ofile = None

    def render(self, inv):
        args = akat.prepare(inv, required_args = ["ofile"])

        global ofile
        ofile = args.ofile

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

