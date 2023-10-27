import os
import sys


def export_level(level_folder, l_id):
    os.system("python image.py {} level{} map {}".format(level_folder, l_id, l_id))


def gen_level_list():
    lines = ("_LVLL",)
    for i in range(int(sys.argv[2])):
        lines = lines+("level{}/lvl.lvljim".format(i),)
    with open("output/level_list", "w") as level_list:
        level_list.write('\n'.join(lines))


def main():
    for i in range(int(sys.argv[2])):
        export_level(sys.argv[1]+"Level_{}/".format(i), i)
        os.system("cp -R {} {}nitrofiles/".format("output/level{}".format(i), sys.argv[3]))
    gen_level_list()
    os.system("cp output/level_list {}nitrofiles/".format(sys.argv[3]))


if __name__ == "__main__":
    main()
