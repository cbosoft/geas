import sys

from editor import Editor

editor = Editor()
editor.load(sys.argv[1])
editor.run()
