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
    for x in range(8):
        for y in range(8):
            if temp_board_occupied % 2:
                piece_image = blackpiece if temp_board_color % 2 else whitepiece
                offset = ((chessboard_width)/8 - piece_width)/2
                screen.blit(piece_image, (chessboard_x + x*grid_width + offset, chessboard_y + y*grid_height + offset))
            print(bin(board_color))
            temp_board_color = temp_board_color >> 1
            temp_board_occupied = temp_board_occupied >> 1

def overall():
    pygame.init()

    size = width, height = 480, 680
    global screen
    screen = pygame.display.set_mode(size)

    global chessboard_width
    chessboard_width = 400
    global chessboard_height
    chessboard_height = 400

    global chessboard_x, chessboard_y, piece_width, piece_height, grid_width, grid_height
    chessboard_x = 40
    chessboard_y = 60

    piece_width = 42
    piece_height = 42

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

    global background, blackpiece, whitepiece

    background = pygame.image.load(background_image_filename).convert()
    blackpiece = pygame.image.load(blackpiece_image_filename).convert_alpha()
    whitepiece = pygame.image.load(whitepiece_image_filename).convert_alpha()

    global color_black, color_white, color_deep_green, color_gray
    color_black = (0,0,0)
    color_white = (255,255,255)
    color_deep_green = (0,87,55)
    color_gray = (50,50,50)

    global board_color, board_occupied

    board_occupied = 0x1818000000
    board_color = 0x810000000



    while 1:
        screen.blit(background, (0,0))

        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()

        draw_chessboard()
        draw_piece()


        pygame.display.flip()