# Script to convert a given asset in png format to a format suitable for PPU466 tile drawing. The script automatically modifies the PlayMode.cpp file and adds the asset info
# The following module needs to be pip installed before running the script - pip install opencv-python
# This is needed to read images 

# opencv read and understood from - https://www.askpython.com/python-modules/read-images-in-python-opencv

from numpy import array
import cv2
from os import listdir
from os.path import isfile, join

# This function compares if all the elements in two given lists match
def cmp_lists(a, b):
    if len(a) != len(b):
        return False
    for i in range(len(a)):
        if a[i] != b[i]:
            return False
    return True

# This funtion checks whether a 1D list exists in a 2D list
def present_in_list(small, bigger):
    for i in range(len(bigger)):
        if len(small) == len(bigger[i]):
            fl = 1
            for j in range(len(small)):
                if small[j] != bigger[i][j]:
                    fl = 0
            if(fl == 1):
                return True

    return False

    
# This function returns the most repeating 1D list, in a 2D list
def max_repeat_val (arr):
    max_ele = arr[0]
    max_cnt = 0
    checked_ele = []

    for i in range(len(arr)):
        if present_in_list(arr[i],checked_ele) == False:
            checked_ele += [arr[i]]
            cnt = 0
            for j in range(len(arr)):
                if cmp_lists(arr[i],arr[j]) == True:
                    cnt += 1
            if cnt > max_cnt:
                max_cnt = cnt
                max_ele = arr[i]
    return list(max_ele)


# This function converts 128x128 pixels worth of information into 8x8 pixels worth of info
def Compress_2_8x8 (img_arr):
    len_r = len(img_arr)
    len_c = len(img_arr[0])
    len_section_r = int(len_r/8)
    len_section_c = int(len_c/8)
    
    quantized_img = array([[[0]*3]*8]*8)

    for major_row in range(0,8):
        for major_col in range(0,8):
            temp_arr = []
            for min_row in range(major_row*len_section_r, major_row*len_section_r + len_section_r):
                for min_col in range(major_col*len_section_c, major_col*len_section_c + len_section_c):
                    temp_arr += [img[min_row][min_col]] # Add values to this array 
            quantized_img[major_row][major_col] = max_repeat_val(temp_arr)
            
    return quantized_img
            
# This function checks the number of colors present in an image then quantizes them to the first 4 colors found
def Quantize_2_4_colors (img_arr):
    quantized_img = array([[[0]*3]*len(img_arr)]*len(img_arr[0]))
    colors = [] #Search the first 4 different colors
    for i in range(len(img_arr)):
        for j in range(len(img_arr[0])):
            quantized_img[i][j] = img_arr[i][j]
            if present_in_list(img_arr[i][j],colors) == False:
                #print(img_arr[i][j])
                if(len(colors) < 4):
                    colors += [img_arr[i][j]]
                else:
                    dist = abs(colors[0][0] - img_arr[i][j][0]) + abs(colors[0][1] - img_arr[i][j][1]) + abs(colors[0][2] - img_arr[i][j][2])
                    index = 0
                    for k in range(len(colors)):
                        curr_dist = abs(colors[k][0] - img_arr[i][j][0]) + abs(colors[k][1] - img_arr[i][j][1]) + abs(colors[k][2] - img_arr[i][j][2]) #Find color distance
                        if (curr_dist < dist):
                            dist = curr_dist
                            index = k
                    quantized_img[i][j] = colors[index]
    
    return quantized_img, colors


# This function converts the pixel 2D information into format suitable for PPU466, generates the code and stores it into a temp file
def write_bitmap(asset_name, img, colors, name, asset_num, palette_num):
    f = open(name, "a+")
    f.write("\n\n// Following code for asset : "+ asset_name + "\n")
    while len(colors) < 4:
        colors += [array([0,0,0])]
    
    
    indices = array([[0]*len(img)]*len(img[0]))

    for i in range(len(img)):
        for j in range(len(img[0])):
            for k in range(len(colors)):
                if cmp_lists(colors[k], img[i][j]) == True:
                    indices[i][j] = k
                    break
    
    bit0 = array([["0"]*8]*8)
    bit1 = array([["0"]*8]*8)

    for i in range(len(indices)):
        for j in range(len(indices[0])):
            if(indices[i][j] == 0):
                bit0[8 - i - 1][8 - j - 1] = "0"
                bit1[8 - i - 1][8 - j - 1] = "0"
            if(indices[i][j] == 1):
                bit0[8 - i - 1][8 - j - 1] = "1"
                bit1[8 - i - 1][8 - j - 1] = "0"
            if(indices[i][j] == 2):
                bit0[8 - i - 1][8 - j - 1] = "0"
                bit1[8 - i - 1][8 - j - 1] = "1"
            if(indices[i][j] == 3):
                bit0[8 - i - 1][8 - j - 1] = "1"
                bit1[8 - i - 1][8 - j - 1] = "1"

    f.write("\nppu.tile_table[" + str(asset_num) +"].bit0 = {\n")
    for i in range(len(bit0)):
        f.write("\t0b" + "".join(bit0[i]) + "," )
        f.write("\n")
    f.write("};\n")

    f.write("\nppu.tile_table[" + str(asset_num) +"].bit1 = {\n")
    for i in range(len(bit1)):
        f.write("\t0b" + "".join(bit1[i]) + ",")
        f.write("\n")
    f.write("};\n")


    f.write("\nppu.palette_table[" + str(palette_num) +"] = {\n")
    for color in colors:
        f.write("\tglm::u8vec4(")
        str1 = ""
        for i in range(len(color) - 1, -1 , -1):
            str1 += "0x" + "0"*(2 - len(hex(color[i])[2:])) + hex(color[i])[2:] + ", "
        f.write(str1 + "0xff")
        f.write("),\n")
    f.write("};\n")
    f.close()


asset_path = "Assets" # Folder where assets are kept. We will scan all images in that folder and create the code. 
out_file_path = "output_code.txt" # Temp file to store the code
playmode_code_path = "PlayMode.cpp" #PlayMode code

asset_num = 0 # Start point in tile table
palette_num = 0 # Start point in palette table
assets = []
fp = open(out_file_path, "w+")
fp.write("")
fp.close()

for item in listdir(asset_path):
    if isfile(join(asset_path, item)):  
        assets += [item]


for asset in assets:
    img = cv2.imread(join(asset_path, asset)) #Reads the image and returns 128x128 pixel information in B,G,R format
    newimg = Compress_2_8x8(img)
    newimg,colors = Quantize_2_4_colors(newimg)
    write_bitmap(asset, newimg, colors, out_file_path, asset_num, palette_num)
    asset_num += 1
    palette_num += 1

f = open("output_code.txt", "r+")
fdata = f.read()
f.close()

finalcode = ""
comment = "// Following asset code developed using asset pipeline script convert_png_2_code.py. \n// The asset pipeline code scans the png sprites, creates the code, and writes it below "
pmflg = 0
cdflg = 0
with open(playmode_code_path , "r+") as fp:
    while True:
        line = fp.readline()
        
        if(line.find("//Insert Code Below") != -1):
            cdflg = 1

        if not line:
            break

fp.close()
check_str = "PlayMode::PlayMode() {"
if(cdflg):
    check_str = "//Insert Code Below"

with open(playmode_code_path , "r+") as fp:
    while True:
        line = fp.readline()
        
        if(line.find(check_str) != -1):
            finalcode += line
            finalcode += "\n" + comment + "\n"
            if(cdflg == 0) : finalcode += "\n//Insert Code Below\n"
            finalcode += fdata
            pmflg = 1
        
        if(line.find("PlayMode::~PlayMode()") != -1):
            finalcode += "\n}\n\n"
            pmflg = 0

        if(pmflg == 0):
            finalcode += line
        
        if not line:
            break

fp.close()

f = open("PlayMode.cpp", "w+")
f.write(finalcode)
f.close()