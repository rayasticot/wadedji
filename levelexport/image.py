import sys
import os
from PIL import Image
import json


PALETTE_SIZE = 8
PALETTE_FILENAME = "palette.png"
COMPOSITE_FILENAME = "_composite.png"
COLLISION_FILENAME = "Collision.png"

COMMAND_BG = "grit {} -g -gTFF00FF -m -mRtf -mLs -p -ftb"
COMMAND_CMAP = "grit {} -g -gT000000 -m -mRt -mLf -p -ftb"
COMMAND_MOVE = "mv {} {}"

MUSIC = (1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
BOSS = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
ENNEMY_INFO = {
    "Item": -1,
    "Pig": 0,
    "Marabout_Fire": 1,
    "Marabout_Thunder": 2,
    "Boss_Genie": 3
}


def rgba_to_indexed(image):
    return image.convert('RGB').quantize(colors=256, method=1)#.convert('P', palette=Image.ADAPTIVE, colors=256)


def add_palette(image):
    new_image = Image.new(image.mode, size = (image.size[0], image.size[1] + PALETTE_SIZE))
    new_image.paste(image, (0, PALETTE_SIZE))
    palette_image = Image.open(PALETTE_FILENAME)
    new_image.paste(palette_image)

    return new_image


def save_image(image, output):
    image_final = rgba_to_indexed(image)
    image_final.save(output)


def create_dir(path):
    if not os.path.exists(path):
        os.makedirs(path)


def grit_cmap():
    os.system(COMMAND_CMAP.format("output/col.bmp"))

    create_dir("output/"+sys.argv[2]+"/")
    os.system(COMMAND_MOVE.format("col.map.bin", "output/"+sys.argv[2]+"/"+"col.cmp"))
    os.system(COMMAND_MOVE.format("col.img.bin", "output/"+sys.argv[2]+"/"+"col.dat"))
    os.system(COMMAND_MOVE.format("col.pal.bin", "output/trash/col.pal"))
    os.system(COMMAND_MOVE.format("col.h", "output/trash/col.h"))


def grit_bg():
    os.system(COMMAND_BG.format("output/map.bmp"))

    os.system(COMMAND_MOVE.format("map.map.bin", "output/"+sys.argv[2]+"/"+sys.argv[3]+".map"))
    os.system(COMMAND_MOVE.format("map.img.bin", "output/"+sys.argv[2]+"/"+sys.argv[3]+".img"))
    os.system(COMMAND_MOVE.format("map.pal.bin", "output/"+sys.argv[2]+"/"+sys.argv[3]+".pal"))
    os.system(COMMAND_MOVE.format("map.h", "output/trash/map.h"))


def read_json_layers(filename):
    with open(filename, "r") as jsonfile:
        jsondata = json.load(jsonfile)
    
    return tuple(jsondata["layers"]), jsondata["width"], jsondata["height"]


def write_bgfile(mape, back, back_scroll):
    lines = ("_BG",)
    lines = lines+(":0", mape[0], "1.0", str(mape[1]), str(mape[2]))
    lines = lines+(":1", back[0], str(back_scroll), str(back[1]), str(back[2]))
    for i in range(2):
        lines = lines+(":{}".format(i+2), "\\")
    lines = lines+(":C", sys.argv[2]+"/col", str(mape[1]), str(mape[2]))

    with open("output/"+sys.argv[2]+"/"+"bg.bgjim", "w") as bgfile:
        bgfile.write('\n'.join(lines))


def write_lvlfile(gfxfile, bgfile):
    lines = ("_LVL", gfxfile, bgfile, str(MUSIC[int(sys.argv[4])]), str(BOSS[int(sys.argv[4])]), "_PLY")
    with open(sys.argv[1]+"data.json") as datafile:
        json_data = json.load(datafile)
        player_start = json_data["entities"]["PlayerStart"][0]
        lines = lines+(str(player_start["x"]), str(player_start["y"]), "_ENN")
        for i, key in enumerate(json_data["entities"]):
            if key == "PlayerStart":
                continue
            for entity in json_data["entities"][key]:
                lines = lines+(str(ENNEMY_INFO[key]), str(entity["x"]), str(entity["y"]), str(entity["customFields"]["health"]), ":")
        lines = lines+("\\",)
    with open("output/"+sys.argv[2]+"/lvl.lvljim", "w") as lvlfile:
        lvlfile.write('\n'.join(lines))


def main():
    images_name, width, height = read_json_layers(sys.argv[1]+"data.json")
    background = Image.new("RGBA", (width, height), color=(255, 0, 255))

    for image_name in images_name:
        if image_name == COLLISION_FILENAME:
            save_image(add_palette(Image.open(sys.argv[1]+COLLISION_FILENAME)), "output/col.bmp")
            continue
        new_image = Image.open(sys.argv[1]+image_name).convert("RGBA")
        background.paste(new_image, (0, 0), new_image)

    save_image(background, "output/map.bmp")
    #save_image(add_palette(Image.open(sys.argv[1]+COLLISION_FILENAME)), "output/col.bmp")
    grit_cmap()
    grit_bg()
    mape = (sys.argv[2]+"/map", width, height)
    back = ("back/grotte", 512, 1024)
    write_bgfile(mape, back, 0.5)
    write_lvlfile("grotte.gfxjim", sys.argv[2]+"/"+"bg.bgjim")


if __name__ == "__main__":
    main()
