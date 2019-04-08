import sys
from pygame import *
import pygame

def draw_chessboard():
    bold = 3
    for i in range(8):
        for j in range(8):
            pygame.draw.rect(screen, color_deep_green, Rect(chessboard_x+grid_width*i,chessboard_y+grid_height*j,grid_width,grid_height))
    for i in range(9):
        pygame.draw.line(screen, color_gray,
            (chessboard_x+grid_width*i,chessboard_y), (chessboard_x+grid_width*i,chessboard_y+chessboard_height), bold)
    for i in range(9):
        pygame.draw.line(screen, color_gray,
            (chessboard_x,chessboard_y+grid_height*i), (chessboard_x+chessboard_width,chessboard_y+grid_height*i), bold)

def draw_piece():
    temp_board_color = board_color
    temp_board_occupied = board_occupied
    for y in range(8):
        for x in range(8):
            if temp_board_occupied % 2:
                piece_image = blackpiece if temp_board_color % 2 else whitepiece
                offset = ((chessboard_width)/8 - piece_width)/2
                screen.blit(piece_image, (chessboard_x + x*grid_width + offset, chessboard_y + y*grid_height + offset))
            temp_board_color = temp_board_color >> 1
            temp_board_occupied = temp_board_occupied >> 1

def draw_hints(posible_moves):
    for i in range(len(posible_moves) / 2):
        x = posible_moves[2*i+1]
        y = posible_moves[2*i]
        offset = ((chessboard_width)/8 - hint_width) / 2
        screen.blit(hintpiece, (chessboard_x + x * grid_width + offset, chessboard_y + y * grid_height + offset))




def init():
    pygame.init()
    size = width, height = 480, 680
    global screen
    screen = pygame.display.set_mode(size)

    global chessboard_width
    chessboard_width = 400
    global chessboard_height
    chessboard_height = 400

    global chessboard_x, chessboard_y, piece_width, piece_height, grid_width, grid_height, hint_width, hint_height
    chessboard_x = 40
    chessboard_y = 60

    piece_width = 42
    piece_height = 42

    hint_width = 10
    hint_height = 10

    grid_width = chessboard_width/8
    grid_height = chessboard_height/8

    global info_x, info_y, info_width, info_height

    info_x = chessboard_x
    info_y = chessboard_y + chessboard_height + 30
    info_width = (chessboard_width / 5) * 4
    info_height = 100


    img_path = 'img/'
    homepage_header_image_filename = img_path + 'homepage_header.png'
    background_image_filename = img_path + 'background.jpg'
    blackpiece_image_filename = img_path + 'black_resize.png'
    whitepiece_image_filename = img_path + 'white_resize.png'
    home_button_image_filename = img_path + 'home_button.png'
    refresh_button_image_filename = img_path + 'refresh_button.png'
    hint_image_filename = img_path + 'hint.PNG'

    global background, blackpiece, whitepiece, hintpiece

    background = pygame.image.load(background_image_filename).convert()
    blackpiece = pygame.image.load(blackpiece_image_filename).convert_alpha()
    whitepiece = pygame.image.load(whitepiece_image_filename).convert_alpha()
    hintpiece = pygame.image.load(hint_image_filename).convert_alpha()

    global color_black, color_white, color_deep_green, color_gray
    color_black = (0,0,0)
    color_white = (255,255,255)
    color_deep_green = (0,87,55)
    color_gray = (50,50,50)

    global board_color, board_occupied

    board_occupied = 0x1818000000
    board_color = 0x810000000


    
def overall(*posible_moves):

    if_click = False
    mouse_position = pygame.mouse.get_pos()

    
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()
        elif event.type == MOUSEBUTTONDOWN:
            if_click = True
    

    screen.blit(background, (0,0))


    draw_chessboard()
    draw_piece()
    print "in python ", posible_moves 
    draw_hints(posible_moves)

    
    if if_click == True:
        real_x = mouse_position[0] - chessboard_x
        real_y = mouse_position[1] - chessboard_y
        if 0 <= real_x <= chessboard_width and 0 <= real_y <= chessboard_height:
            return (real_x / grid_width, real_y / grid_height)
    

    pygame.display.flip()
    return (-1, -1)

