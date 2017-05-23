import re

npatt = re.compile('^(\d*)([A-Z]#?)(\d*)(\.?)$')

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["oname", "text"])

        d = 4 # Duration of a note (default is 1/4 of note)
        b = 108 # Tempo (beats per minute)
        o = 1 # Octave

        settings, text = ctx.text.replace("\"", "").split(":", 1)
        for kv in settings.split(","):
            k, v = kv.split("=", 1)
            k = k.strip()
            v = v.strip()
            if k == "d":
                d = int(v)
            elif k == "b":
                b = int(v)
            elif k == "o":
                o = int(v)
            else:
                akat.fatal_error("No idea how to parse settings part, strange kv pair: ", STRESS(kv))

        tempo_deciseconds = int(60 * 60 * 10 / b)

        sounds = []

        for t in text.split(","):
            t = t.strip().upper()

            # Format:
            # 1. Optional duration 1,2,4... (means 1/1, 1/2, 1/4 of tempo value)
            # 2. Note like A1, A3, B#...
            # 3. Dot, means add 1/2 of orignal note duration
            nd = d
            no = o
            has_dot = False

            m = npatt.match(t)
            if m:
                gdur = m.group(1)
                n = m.group(2).replace("#", "S")
                go = m.group(3)
                gdot = m.group(4)

                if gdur != "":
                    nd = int(gdur)

                if go != "":
                    no = int(go)

                if gdot != "":
                    has_dot = True
            else:
                akat.fatal_error("No idea how to parse: ", STRESS(t))

            if nd == 1 and has_dot:
                akat.fatal_error("This note is longer than a note: ", STRESS(t))

            note_deciseconds = tempo_deciseconds / (nd + 0.0)
            if has_dot:
                note_deciseconds += note_deciseconds / 2.

            note_deciseconds = int(note_deciseconds)

            if note_deciseconds == 0:
                akat.fatal_error("Note can't has zero deciseconds length: ", STRESS(t))

            n = n + str(no)

            pause = tempo_deciseconds - note_deciseconds

            while note_deciseconds > 0:
                sound_deciseconds = note_deciseconds > 255 and 255 or note_deciseconds
                sounds.append(str(sound_deciseconds) + " @ " + n)
                note_deciseconds -= 255

            while pause > 0:
                sound_deciseconds = pause > 255 and 255 or pause
                sounds.append(str(sound_deciseconds) + " @ 0")
                pause -= 255

        return akat.transform(akat.render(self, sounds = sounds, oname = ctx.oname))
