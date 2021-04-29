#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define SYMBOL_2D_POINT_COUNT 215
#define SYMBOL_2D_TRIANGLE_COUNT 213

unsigned int SELECTED_LETTERID = -1;

const unsigned int SIMBOL_WIDTH = 401;
const unsigned int SIMBOL_HEIGHT = 445;

// screen settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//
const int NUMBER_LETTERS = 5;
float speed = 10.0f;

const glm::mat4 INITIAL_TRANSLATIONS[NUMBER_LETTERS] = {
        glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f))
};


// camera settings
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); // and looks at the origin
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);  // Head is up (set to 0,1,0 to look upside-down)


// MVP MATRIX GLOBAL VARIABLES
// Model matrix : an identity matrix (model will be at the origin)
//glm::mat4 MODEL = glm::mat4(1.0f);

// View camera matrix
glm::mat4 VIEW = glm::lookAt(
        cameraPos, //in World Space
        cameraFront, // and looks at the origin
        cameraUp // Head 
);

glm::mat4 PROJECTION; // In world coordinates

glm::mat4 TRANSLATION[NUMBER_LETTERS];

glm::mat4 MODEL[NUMBER_LETTERS];

glm::mat4 MVP[NUMBER_LETTERS];


void genColors(float *colors, int colors_count) {
    srand(5674389);
    for (int i = 0; i < colors_count; i++) {
        colors[i] = ((float) rand()) / (float) RAND_MAX;
    }

}

//TODO CAN BE USEFUL LATER
//void drawLetter(float *indices, int index, GLint MatrixID, unsigned int *VAO, int vertexColorLocation,
//                 glm::vec4 *selected_colors) {
//    glBindVertexArray(VAO[index]);
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[index][0][0]);
//    glUniform4f(vertexColorLocation, selected_colors[index][0], selected_colors[index][1], selected_colors[index][2],
//                selected_colors[index][3]);
//    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, nullptr);
//}

//============================================
/* process all input: query GLFW whether relevant keys are pressed/released 
this frame and react accordingly 
-----------------------------------------------------------------------*/


void letterPosition() {
    TRANSLATION[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f));
    TRANSLATION[1] = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));
    TRANSLATION[2] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    TRANSLATION[3] = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));
    TRANSLATION[4] = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
}


glm::vec4 selected_colors[] = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
};



void moveLetter(GLFWwindow *window) {
    static double cursor_x;
    static double cursor_y;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);
    cursor_x = (cursor_x - SCR_WIDTH / 2) / ((SCR_WIDTH / 2) / 4);
    cursor_y = -(cursor_y - SCR_HEIGHT / 2) / ((SCR_HEIGHT / 2) / 4);
//    printf("Cursor position: %f %f\n", cursor_x, cursor_y);
    if (SELECTED_LETTERID != -1) {
        TRANSLATION[SELECTED_LETTERID] = glm::translate(glm::mat4(1.0f), glm::vec3(cursor_x, cursor_y,
                                                                                   TRANSLATION[SELECTED_LETTERID][3][2]));
    }
}

void moveLetterOverZ(GLFWwindow *window, char symbol) {

    if (SELECTED_LETTERID != -1) {
        TRANSLATION[SELECTED_LETTERID] = symbol == '+' ?
                                         glm::translate(TRANSLATION[SELECTED_LETTERID], glm::vec3(0.0f, 0.0f, 0.5f))
                                                       :
                                         glm::translate(TRANSLATION[SELECTED_LETTERID], glm::vec3(0.0f, 0.0f, -0.5f));
    }
}

void moveLetterOverX(GLFWwindow *window, char symbol) {

    if (SELECTED_LETTERID != -1) {
        switch (symbol) {
            case 'U':
                MODEL[SELECTED_LETTERID] = glm::rotate(MODEL[SELECTED_LETTERID], glm::radians(speed),
                                                       glm::vec3(1.0, 0.0, 0.0));
                break;
            case 'D':
                MODEL[SELECTED_LETTERID] = glm::rotate(MODEL[SELECTED_LETTERID], glm::radians(-speed),
                                                       glm::vec3(1.0, 0.0, 0.0));
                break;

        }
    }
}

void moveLetterOverY(GLFWwindow *window, char symbol) {

    if (SELECTED_LETTERID != -1) {
        switch (symbol) {
            case 'R':
                MODEL[SELECTED_LETTERID] = glm::rotate(MODEL[SELECTED_LETTERID], glm::radians(speed),
                                                       glm::vec3(0.0, 1.0, 0.0));
                break;
            case 'L':
                MODEL[SELECTED_LETTERID] = glm::rotate(MODEL[SELECTED_LETTERID], glm::radians(-speed),
                                                       glm::vec3(0.0, 1.0, 0.0));
                break;

        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        moveLetterOverY(window, 'R');
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        moveLetterOverX(window, 'U');
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        moveLetterOverX(window, 'D');
    } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        moveLetterOverY(window, 'L');
    }
}


void selectLetterV2(int letter) {

    glm::vec4 selected_color = glm::vec4(1, 1, 1, 1);
    selected_colors[letter] = selected_color;
}

void reset_positions() {
    TRANSLATION[0] = INITIAL_TRANSLATIONS[0];
    TRANSLATION[1] = INITIAL_TRANSLATIONS[1];
    TRANSLATION[2] = INITIAL_TRANSLATIONS[2];
    TRANSLATION[3] = INITIAL_TRANSLATIONS[3];
    TRANSLATION[4] = INITIAL_TRANSLATIONS[4];
    MODEL[0] = glm::mat4(1.0f);
    MODEL[1] = glm::mat4(1.0f);
    MODEL[2] = glm::mat4(1.0f);
    MODEL[3] = glm::mat4(1.0f);
    MODEL[4] = glm::mat4(1.0f);
}

void selectLetter(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
        selectLetterV2(0);
        SELECTED_LETTERID = 0;
    } else if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
        selectLetterV2(1);
        SELECTED_LETTERID = 1;
    } else if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS) {
        selectLetterV2(2);
        SELECTED_LETTERID = 2;
    } else if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS) {
        selectLetterV2(3);
        SELECTED_LETTERID = 3;
    } else if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS) {
        selectLetterV2(4);
        SELECTED_LETTERID = 4;
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        reset_positions();
    } else if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS &&
               (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)) {
        moveLetterOverZ(window, '+');
    } else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS &&
               (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)) {
        moveLetterOverZ(window, '-');
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        moveLetter(window);
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        speed += 1.0;
        std::cout << speed << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        if (speed > 1.0) {
            speed -= 1.0f;
        } else {
            speed = 1.0f;
        }
        std::cout << speed << std::endl;
    }

    glfwSetKeyCallback(window, key_callback);
}



void colorCustom(int i) {
    if(i == 0 && SELECTED_LETTERID != 0)
    {
        selected_colors[i] = glm::vec4(1, 0, 0, 1);
    } else if(i == 1 && SELECTED_LETTERID != 1) {
        selected_colors[i] = glm::vec4(0, 1, 0, 1);
    }else if(i == 2 && SELECTED_LETTERID != 2) {
        selected_colors[i] = glm::vec4(0, 0, 1, 1);
    }else if(i == 3 && SELECTED_LETTERID != 3) {
        selected_colors[i] = glm::vec4(0, 1, 1, 1);
    }else if(i == 4 && SELECTED_LETTERID != 4) {
        selected_colors[i] = glm::vec4(1, 1, 0, 1);
    }
}

void colorBlack() {
    for (int i = 0; i < 5; ++i) {
        if(SELECTED_LETTERID != i) selected_colors[i] = glm::vec4(0, 0, 0, 1);
    }
}


// FOR LETTER Beyblades

float normalize_x(float x) {
    x /= (SCR_WIDTH / 2); //TODO mudei para a escala da janela para ficar do tamanho das outras letras
    x -= 1;
    return x;
}


float normalize_y(float y) {
    y /= (SCR_HEIGHT / 2); //TODO mudei para a escala da janela para ficar do tamanho das outras letras
    y -= 1;
    return -y;
}


unsigned int get_next_point(unsigned int prev) {
    unsigned int result;
    switch (prev) {
        case 36:
            result = 0;
            break;
        case 17:
            result = 37;
            break;
        case 74:
            result = 127;
            break;
        case 214:
            result = 75;
            break;
        case 126:
            result = 18;
            break;
        default:
            result = prev + 1;
            break;
    }
    return result;
}

void get_symbol_points(float *vertices, int vertices_size, unsigned int *indices, int indices_size, float depth) {
    float symbol_2D_points[] = {
            //first segment
            normalize_x(197), normalize_y(355), 0.0f, //0
            normalize_x(203), normalize_y(353), 0.0f, //1
            normalize_x(209), normalize_y(354), 0.0f,
            normalize_x(213), normalize_y(356), 0.0f,
            normalize_x(220), normalize_y(359), 0.0f,
            normalize_x(225), normalize_y(361), 0.0f, //5
            normalize_x(231), normalize_y(363), 0.0f,
            normalize_x(243), normalize_y(366), 0.0f,
            normalize_x(252), normalize_y(368), 0.0f,
            normalize_x(263), normalize_y(370), 0.0f,
            normalize_x(267), normalize_y(371), 0.0f, //10
            normalize_x(273), normalize_y(370), 0.0f,
            normalize_x(279), normalize_y(367), 0.0f,
            normalize_x(284), normalize_y(365), 0.0f,
            normalize_x(290), normalize_y(361), 0.0f,
            normalize_x(296), normalize_y(356), 0.0f, //15
            normalize_x(302), normalize_y(351), 0.0f,
            normalize_x(305), normalize_y(345), 0.0f,
            normalize_x(312), normalize_y(358), 0.0f,
            normalize_x(305), normalize_y(364), 0.0f,
            normalize_x(297), normalize_y(369), 0.0f, //20
            normalize_x(290), normalize_y(373), 0.0f,
            normalize_x(279), normalize_y(378), 0.0f,
            normalize_x(263), normalize_y(382), 0.0f,
            normalize_x(252), normalize_y(384), 0.0f,
            normalize_x(243), normalize_y(385), 0.0f, //25
            normalize_x(231), normalize_y(385), 0.0f,
            normalize_x(219), normalize_y(383), 0.0f,
            normalize_x(207), normalize_y(380), 0.0f,
            normalize_x(200), normalize_y(378), 0.0f,
            normalize_x(194), normalize_y(375), 0.0f, //30
            normalize_x(187), normalize_y(372), 0.0f,
            normalize_x(184), normalize_y(371), 0.0f,
            normalize_x(182), normalize_y(369), 0.0f,
            normalize_x(183), normalize_y(367), 0.0f,
            normalize_x(188), normalize_y(361), 0.0f, //35
            normalize_x(193), normalize_y(357), 0.0f,

            //second segment
            normalize_x(310), normalize_y(340), 0.0f,
            normalize_x(313), normalize_y(334), 0.0f,
            normalize_x(316), normalize_y(329), 0.0f,
            normalize_x(319), normalize_y(323), 0.0f, //40
            normalize_x(323), normalize_y(315), 0.0f,
            normalize_x(327), normalize_y(306), 0.0f,
            normalize_x(329), normalize_y(298), 0.0f,
            normalize_x(333), normalize_y(288), 0.0f,
            normalize_x(336), normalize_y(280), 0.0f, //45
            normalize_x(336), normalize_y(276), 0.0f,
            normalize_x(334), normalize_y(275), 0.0f,
            normalize_x(331), normalize_y(276), 0.0f,
            normalize_x(328), normalize_y(279), 0.0f,
            normalize_x(323), normalize_y(281), 0.0f, //50
            normalize_x(317), normalize_y(284), 0.0f,
            normalize_x(310), normalize_y(287), 0.0f,
            normalize_x(306), normalize_y(290), 0.0f,
            normalize_x(301), normalize_y(293), 0.0f,
            normalize_x(296), normalize_y(295), 0.0f, //55
            normalize_x(289), normalize_y(299), 0.0f,
            normalize_x(283), normalize_y(301), 0.0f,
            normalize_x(277), normalize_y(303), 0.0f,
            normalize_x(268), normalize_y(306), 0.0f,
            normalize_x(259), normalize_y(308), 0.0f, //60
            normalize_x(251), normalize_y(309), 0.0f,
            normalize_x(244), normalize_y(310), 0.0f,
            normalize_x(234), normalize_y(309), 0.0f,
            normalize_x(227), normalize_y(307), 0.0f,
            normalize_x(220), normalize_y(305), 0.0f, //65
            normalize_x(213), normalize_y(303), 0.0f,
            normalize_x(208), normalize_y(300), 0.0f,
            normalize_x(203), normalize_y(296), 0.0f,
            normalize_x(199), normalize_y(293), 0.0f,
            normalize_x(196), normalize_y(290), 0.0f, //70
            normalize_x(193), normalize_y(286), 0.0f,
            normalize_x(189), normalize_y(282), 0.0f,
            normalize_x(187), normalize_y(278), 0.0f,
            normalize_x(184), normalize_y(274), 0.0f,
            normalize_x(215), normalize_y(263), 0.0f, //75
            normalize_x(218), normalize_y(268), 0.0f,
            normalize_x(222), normalize_y(271), 0.0f,
            normalize_x(226), normalize_y(274), 0.0f,
            normalize_x(230), normalize_y(278), 0.0f,
            normalize_x(238), normalize_y(283), 0.0f, //80
            normalize_x(246), normalize_y(287), 0.0f,
            normalize_x(260), normalize_y(290), 0.0f,
            normalize_x(268), normalize_y(291), 0.0f,
            normalize_x(273), normalize_y(291), 0.0f,
            normalize_x(281), normalize_y(290), 0.0f, //85
            normalize_x(289), normalize_y(289), 0.0f,
            normalize_x(294), normalize_y(288), 0.0f,
            normalize_x(300), normalize_y(285), 0.0f,
            normalize_x(306), normalize_y(282), 0.0f,
            normalize_x(311), normalize_y(278), 0.0f, //90
            normalize_x(316), normalize_y(275), 0.0f,
            normalize_x(321), normalize_y(272), 0.0f,
            normalize_x(325), normalize_y(269), 0.0f,
            normalize_x(327), normalize_y(265), 0.0f,
            normalize_x(331), normalize_y(261), 0.0f, //95
            normalize_x(334), normalize_y(257), 0.0f,
            normalize_x(337), normalize_y(253), 0.0f,
            normalize_x(341), normalize_y(247), 0.0f,
            normalize_x(344), normalize_y(241), 0.0f,
            normalize_x(348), normalize_y(231), 0.0f, //100
            normalize_x(352), normalize_y(223), 0.0f,
            normalize_x(354), normalize_y(216), 0.0f,
            normalize_x(357), normalize_y(211), 0.0f,
            normalize_x(360), normalize_y(205), 0.0f,
            normalize_x(363), normalize_y(202), 0.0f, //105
            normalize_x(370), normalize_y(199), 0.0f,
            normalize_x(375), normalize_y(195), 0.0f,
            normalize_x(380), normalize_y(196), 0.0f,
            normalize_x(381), normalize_y(199), 0.0f,
            normalize_x(380), normalize_y(206), 0.0f, //110
            normalize_x(379), normalize_y(214), 0.0f,
            normalize_x(377), normalize_y(225), 0.0f,
            normalize_x(373), normalize_y(239), 0.0f,
            normalize_x(370), normalize_y(247), 0.0f,
            normalize_x(366), normalize_y(261), 0.0f, //115
            normalize_x(363), normalize_y(270), 0.0f,
            normalize_x(359), normalize_y(281), 0.0f,
            normalize_x(356), normalize_y(289), 0.0f,
            normalize_x(352), normalize_y(300), 0.0f,
            normalize_x(348), normalize_y(309), 0.0f, //120
            normalize_x(344), normalize_y(314), 0.0f,
            normalize_x(339), normalize_y(324), 0.0f,
            normalize_x(335), normalize_y(329), 0.0f,
            normalize_x(328), normalize_y(339), 0.0f,
            normalize_x(323), normalize_y(348), 0.0f, //125
            normalize_x(317), normalize_y(354), 0.0f,

            //third segment
            normalize_x(180), normalize_y(266), 0.0f,
            normalize_x(177), normalize_y(255), 0.0f,
            normalize_x(175), normalize_y(242), 0.0f,
            normalize_x(174), normalize_y(231), 0.0f, //130
            normalize_x(174), normalize_y(222), 0.0f,
            normalize_x(175), normalize_y(213), 0.0f,
            normalize_x(176), normalize_y(201), 0.0f,
            normalize_x(178), normalize_y(191), 0.0f,
            normalize_x(181), normalize_y(181), 0.0f, //135
            normalize_x(184), normalize_y(171), 0.0f,
            normalize_x(187), normalize_y(163), 0.0f,
            normalize_x(191), normalize_y(155), 0.0f,
            normalize_x(197), normalize_y(145), 0.0f,
            normalize_x(204), normalize_y(133), 0.0f, //140
            normalize_x(210), normalize_y(126), 0.0f,
            normalize_x(218), normalize_y(116), 0.0f,
            normalize_x(226), normalize_y(108), 0.0f,
            normalize_x(233), normalize_y(101), 0.0f,
            normalize_x(239), normalize_y(97), 0.0f, //145
            normalize_x(245), normalize_y(92), 0.0f,
            normalize_x(252), normalize_y(86), 0.0f,
            normalize_x(262), normalize_y(80), 0.0f,
            normalize_x(274), normalize_y(74), 0.0f,
            normalize_x(278), normalize_y(72), 0.0f, //150
            normalize_x(286), normalize_y(68), 0.0f,
            normalize_x(294), normalize_y(65), 0.0f,
            normalize_x(299), normalize_y(64), 0.0f,
            normalize_x(305), normalize_y(62), 0.0f,
            normalize_x(310), normalize_y(60), 0.0f, //155
            normalize_x(317), normalize_y(59), 0.0f,
            normalize_x(326), normalize_y(58), 0.0f,
            normalize_x(332), normalize_y(57), 0.0f,
            normalize_x(345), normalize_y(57), 0.0f,
            normalize_x(370), normalize_y(58), 0.0f, //160
            normalize_x(379), normalize_y(60), 0.0f,
            normalize_x(385), normalize_y(63), 0.0f,
            normalize_x(391), normalize_y(67), 0.0f,
            normalize_x(394), normalize_y(72), 0.0f,
            normalize_x(395), normalize_y(78), 0.0f, //165
            normalize_x(395), normalize_y(84), 0.0f,
            normalize_x(394), normalize_y(90), 0.0f,
            normalize_x(392), normalize_y(96), 0.0f,
            normalize_x(390), normalize_y(101), 0.0f,
            normalize_x(387), normalize_y(108), 0.0f, //170
            normalize_x(380), normalize_y(118), 0.0f,
            normalize_x(374), normalize_y(125), 0.0f,
            normalize_x(365), normalize_y(133), 0.0f,
            normalize_x(359), normalize_y(138), 0.0f,
            normalize_x(353), normalize_y(140), 0.0f, //175
            normalize_x(350), normalize_y(140), 0.0f,
            normalize_x(351), normalize_y(137), 0.0f,
            normalize_x(356), normalize_y(131), 0.0f,
            normalize_x(360), normalize_y(124), 0.0f,
            normalize_x(362), normalize_y(119), 0.0f, //180
            normalize_x(368), normalize_y(105), 0.0f,
            normalize_x(370), normalize_y(99), 0.0f,
            normalize_x(370), normalize_y(95), 0.0f,
            normalize_x(369), normalize_y(91), 0.0f,
            normalize_x(366), normalize_y(86), 0.0f, //185
            normalize_x(363), normalize_y(81), 0.0f,
            normalize_x(356), normalize_y(76), 0.0f,
            normalize_x(349), normalize_y(74), 0.0f,
            normalize_x(342), normalize_y(72), 0.0f,
            normalize_x(325), normalize_y(71), 0.0f, //190
            normalize_x(304), normalize_y(72), 0.0f,
            normalize_x(290), normalize_y(73), 0.0f,
            normalize_x(283), normalize_y(76), 0.0f,
            normalize_x(273), normalize_y(80), 0.0f,
            normalize_x(268), normalize_y(83), 0.0f, //195
            normalize_x(261), normalize_y(87), 0.0f,
            normalize_x(256), normalize_y(91), 0.0f,
            normalize_x(252), normalize_y(94), 0.0f,
            normalize_x(248), normalize_y(97), 0.0f,
            normalize_x(241), normalize_y(104), 0.0f, //200
            normalize_x(235), normalize_y(112), 0.0f,
            normalize_x(229), normalize_y(120), 0.0f,
            normalize_x(222), normalize_y(133), 0.0f,
            normalize_x(215), normalize_y(147), 0.0f,
            normalize_x(211), normalize_y(158), 0.0f, //205
            normalize_x(208), normalize_y(168), 0.0f,
            normalize_x(206), normalize_y(180), 0.0f,
            normalize_x(205), normalize_y(189), 0.0f,
            normalize_x(204), normalize_y(201), 0.0f,
            normalize_x(203), normalize_y(211), 0.0f, //210
            normalize_x(203), normalize_y(226), 0.0f,
            normalize_x(204), normalize_y(235), 0.0f,
            normalize_x(206), normalize_y(243), 0.0f,
            normalize_x(209), normalize_y(251), 0.0f

    };

    unsigned int symbol_2D_indices[] = {  // note that we start from 0!
            //topside of segment 1
            36, 35, 31,
            0, 36, 30,
            1, 0, 30,
            2, 1, 30,
            3, 2, 29,
            4, 3, 28,
            5, 4, 27,
            6, 5, 27,
            7, 6, 26,
            8, 7, 25,
            9, 8, 24,
            10, 9, 23,
            11, 10, 23,
            12, 11, 22,
            13, 12, 22,
            14, 13, 21,
            15, 14, 20,
            16, 15, 19,
            17, 16, 18,

            //underside of segment 1
            18, 16, 19,
            19, 15, 20,
            20, 14, 21,
            21, 13, 22,
            22, 11, 23,
            23, 9, 24,
            24, 8, 25,
            25, 7, 26,
            26, 6, 27,
            27, 4, 28,
            28, 3, 29,
            29, 2, 30,
            30, 36, 31,
            31, 35, 32,
            32, 35, 33,
            33, 35, 34,

            //topside of segment 2
            37, 17, 126,
            38, 37, 125,
            39, 38, 124,
            40, 39, 123,
            41, 40, 122,
            42, 41, 121,
            43, 42, 120,
            44, 43, 119,
            45, 44, 118,
            46, 45, 117,
            47, 46, 96, //might be wrong
            48, 47, 95, //might be wrong
            49, 48, 93, //might be wrong
            50, 49, 92,
            51, 50, 91,
            52, 51, 90,
            53, 52, 89,
            54, 53, 88,
            55, 54, 87,
            56, 55, 86,
            57, 56, 85,
            58, 57, 84,
            59, 58, 83,
            60, 59, 82,
            61, 60, 81,
            62, 61, 80,
            63, 62, 79,
            64, 63, 79,
            65, 64, 79,
            66, 65, 78,
            67, 66, 78,
            68, 67, 77,
            69, 68, 77,
            70, 69, 77,
            71, 70, 76,
            72, 71, 76,
            73, 72, 75,
            74, 73, 75,

            97, 46, 116,

            //underside of segment 2
            76, 75, 72,
            77, 76, 70,
            78, 77, 67,
            79, 78, 65,
            80, 79, 62,
            81, 80, 61,
            82, 81, 60,
            83, 82, 59,
            84, 83, 58,
            85, 84, 57,
            86, 85, 56,
            87, 86, 55,
            88, 87, 54,
            89, 88, 53,
            90, 89, 52,
            91, 90, 51,
            92, 91, 50,
            93, 92, 49,
            94, 93, 48,
            95, 94, 48,
            96, 95, 47,
            97, 96, 46,
            98, 97, 115,
            99, 98, 114,
            100, 99, 112,
            101, 100, 112,
            102, 101, 111,
            103, 102, 111,
            104, 103, 110,
            105, 104, 110,
            106, 105, 110,
            107, 106, 108,
            109, 108, 106,
            110, 109, 106,
            111, 110, 103,
            112, 111, 101,
            113, 112, 99,
            114, 113, 99,
            115, 114, 98,
            116, 115, 97,
            117, 116, 46,
            118, 117, 45,
            119, 118, 44,
            120, 119, 43,
            121, 120, 42,
            122, 121, 41,
            123, 122, 40,
            124, 123, 39,
            125, 124, 38,
            126, 125, 37,
            18, 126, 17,

            //topside of segment 3
            127, 74, 75,
            128, 127, 214,
            129, 128, 213,
            130, 129, 212,
            131, 130, 211,
            132, 131, 210,
            133, 132, 209,
            134, 133, 208,
            135, 134, 207,
            136, 135, 206,
            137, 136, 205,
            138, 137, 204,
            139, 138, 204,
            140, 139, 204,
            141, 140, 203,
            142, 141, 202,
            143, 142, 201,
            144, 143, 200,
            145, 144, 200,
            146, 145, 199,
            147, 146, 198,
            148, 147, 196,
            149, 148, 194,
            150, 149, 193,
            151, 150, 192,
            152, 151, 191,
            153, 152, 191,
            154, 153, 191,
            155, 154, 191,
            156, 155, 190,
            157, 156, 190,
            158, 157, 190,
            159, 158, 189,
            160, 159, 188,
            161, 160, 187,
            162, 161, 186,
            163, 162, 186,
            164, 163, 185,
            165, 164, 185,
            166, 165, 185,
            167, 166, 184,
            168, 167, 183,
            169, 168, 182,
            170, 169, 182,
            171, 170, 181,
            172, 171, 180,
            173, 172, 179,
            174, 173, 178,
            175, 174, 177,
            176, 175, 177,
            178, 177, 174,
            179, 178, 173,
            180, 179, 172,
            181, 180, 171,
            182, 181, 170,
            183, 182, 168,
            184, 183, 167,
            185, 184, 166,
            186, 185, 163,
            187, 186, 161,
            188, 187, 160,
            189, 188, 159,
            190, 189, 158,
            191, 190, 155,
            192, 191, 151,
            193, 192, 150,
            194, 193, 149,
            195, 194, 148,
            196, 195, 148,
            197, 196, 147,
            198, 197, 147,
            199, 198, 146,
            200, 199, 145,
            201, 200, 143,
            202, 201, 142,
            203, 202, 141,
            204, 203, 140,
            205, 204, 137,
            206, 205, 136,
            207, 206, 135,
            208, 207, 134,
            209, 208, 133,
            210, 209, 132,
            211, 210, 131,
            212, 211, 130,
            213, 212, 129,
            214, 213, 128,
            75, 214, 127
    };

    int vertices_front_size = vertices_size;
    int vertices_back_size = 0;
    int indices_front_size = indices_size;
    int indices_back_size = 0;
    int indices_side_size = 0;
    if (depth > 0.0f) {
        vertices_front_size /= 2;
        vertices_back_size = vertices_front_size;

        //not sure

        indices_side_size = vertices_front_size * 2;
        indices_front_size = (indices_front_size - indices_side_size) / 2;
        //printf("%u", indices_front_size);
        indices_back_size = indices_front_size;
        //not sure
    }
    //printf("vertice: ");
    for (int i = 0; i < vertices_front_size; i++) {
        if (i % 3 != 2) {
            vertices[i] = symbol_2D_points[i];
            //printf("%f, ", vertices[i]);
        } else {
            vertices[i] = symbol_2D_points[i] + depth / 2;
            //printf("%f\nvertice: ", vertices[i]);
        }
    }

    //printf("Back vertice: ");
    for (int i = 0; i < vertices_back_size; i++) {
        if (i % 3 != 2) {
            vertices[i + vertices_front_size] = symbol_2D_points[i];
            //printf("%f, ", vertices[i + vertices_front_size]);
        } else {
            vertices[i + vertices_front_size] = symbol_2D_points[i] - depth / 2;
            //printf("%f\nBack vertice: ", vertices[i + vertices_front_size]);
        }
    }

    //printf("indice: ");
    for (int i = 0; i < indices_front_size; i++) {
        indices[i] = symbol_2D_indices[i];
        //if (i % 3 != 2)
        //{
        //	printf("%u, ", indices[i]);
        //}
        //else
        //{
        //	printf("%u\nindice: ", indices[i]);
        //}
    }

    for (int i = 0; i < indices_back_size; i += 3) {
        indices[i + indices_front_size] = symbol_2D_indices[i + 2] + vertices_front_size / 3;
        indices[i + indices_front_size + 1] = symbol_2D_indices[i + 1] + vertices_front_size / 3;
        indices[i + indices_front_size + 2] = symbol_2D_indices[i] + vertices_front_size / 3;

        //printf("Back indice: %u, %u, %u\n", indices[i + indices_front_size], indices[i + indices_front_size + 1], indices[i + indices_front_size + 2]);
    }

    unsigned int current_point = 0;
    for (int i = 0; i < indices_side_size; i += 6) {
        unsigned int next_point = get_next_point(current_point);
        indices[i + indices_front_size + indices_back_size] = current_point;
        indices[i + indices_front_size + indices_back_size + 1] = next_point;
        indices[i + indices_front_size + indices_back_size + 2] = next_point + vertices_front_size / 3;


        indices[i + indices_front_size + indices_back_size + 3] = current_point;
        indices[i + indices_front_size + indices_back_size + 4] = next_point + vertices_front_size / 3;
        indices[i + indices_front_size + indices_back_size + 5] = current_point + vertices_front_size / 3;
        //printf("current point: %u\n", current_point);
        //printf("triag1: %u, %u, %u\n", indices[i + indices_front_size + indices_back_size], indices[i + indices_front_size + indices_back_size + 1], indices[i + indices_front_size + indices_back_size + 2]);
        //printf("triag2: %u, %u, %u\n", indices[i + indices_front_size + indices_back_size + 3], indices[i + indices_front_size + indices_back_size + 4], indices[i + indices_front_size + indices_back_size + 5]);
        //printf("--------------------------------\n");

        current_point = next_point;
    }
}


/* glfw: whenever the window size changed (by OS or user resize) this
   callback function executes
   -------------------------------------------------------------------*/
// Funcao que cria a janela e deteta movimento, dimensoes,etc
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that
    // width and height will be significantly larger than specified on
    // retina displays.
    glViewport(0, 0, width, height);
}


int main() {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sopa de Letras", nullptr,
                                          nullptr);


    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


//------------------------------------------------------------
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // set up vertex data with depth
// ----------------------------------------

    /// ARRAYS -----------------------LETTER BETA-------------------------------------/

    // One color for each vertex. They were generated randomly.
    static const float color_beta[] =
            {
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
                    0.014f, 0.184f, 0.576f,
                    0.771f, 0.328f, 0.970f,
                    0.406f, 0.615f, 0.116f,
                    0.676f, 0.977f, 0.133f,
                    0.971f, 0.572f, 0.833f,
                    0.140f, 0.616f, 0.489f,
                    0.997f, 0.513f, 0.064f,
                    0.945f, 0.719f, 0.592f,
                    0.543f, 0.021f, 0.978f,
                    0.279f, 0.317f, 0.505f,
                    0.167f, 0.620f, 0.077f,
                    0.347f, 0.857f, 0.137f,
                    0.055f, 0.953f, 0.042f,
                    0.714f, 0.505f, 0.345f,
                    0.783f, 0.290f, 0.734f,
                    0.722f, 0.645f, 0.174f,
                    0.302f, 0.455f, 0.848f,
                    0.225f, 0.587f, 0.040f,
                    0.517f, 0.713f, 0.338f,
                    0.053f, 0.959f, 0.120f,
                    0.393f, 0.621f, 0.362f,
                    0.673f, 0.211f, 0.457f,
                    0.820f, 0.883f, 0.371f,
                    0.982f, 0.099f, 0.879f,
                    0.583f, 0.771f, 0.014f,
                    0.609f, 0.115f, 0.436f,
                    0.327f, 0.483f, 0.844f,
                    0.822f, 0.569f, 0.201f,
                    0.435f, 0.602f, 0.223f,
                    0.310f, 0.747f, 0.185f,
                    0.597f, 0.770f, 0.761f,
                    0.559f, 0.436f, 0.730f,
                    0.359f, 0.583f, 0.152f,
                    0.483f, 0.596f, 0.789f,
                    0.559f, 0.861f, 0.639f,
                    0.195f, 0.548f, 0.859f,
            };

    static const float vertices_beta[] = {
            -0.204135, -0.488759, 0.027943,
            -0.216556, -0.472198, 0.027943,
            -0.213303, -0.277009, 0.027943,
            -0.213007, -0.179415, 0.027943,
            -0.211824, -0.069991, 0.027943,
            -0.210937, -0.003745, 0.027943,
            -0.208867, 0.07433, 0.027943,
            -0.206797, 0.13614, 0.027943,
            -0.20236, 0.196471, 0.027943,
            -0.197037, 0.242311, 0.027943,
            -0.190235, 0.278391, 0.027943,
            -0.17811, 0.320682, 0.027943,
            -0.158591, 0.35972, 0.027943,
            -0.132566, 0.396096, 0.027943,
            -0.09826, 0.430697, 0.027943,
            -0.058039, 0.455835, 0.027943,
            -0.011904, 0.473284, 0.027943,
            0.03157, 0.480973, 0.027943,
            0.072087, 0.482156, 0.027943,
            0.104322, 0.475354, 0.027943,
            0.12946, 0.464116, 0.027943,
            0.146613, 0.453765, 0.027943,
            0.162287, 0.440161, 0.027943,
            0.176779, 0.4236, 0.027943,
            0.1892, 0.404672, 0.027943,
            0.197776, 0.383379, 0.027943,
            0.204282, 0.35765, 0.027943,
            0.204874, 0.317429, 0.027943,
            0.198368, 0.290221, 0.027943,
            0.190383, 0.269519, 0.027943,
            0.179736, 0.247043, 0.027943,
            0.16347, 0.222201, 0.027943,
            0.138037, 0.194105, 0.027943,
            0.121771, 0.181093, 0.027943,
            0.102252, 0.16808, 0.027943,
            0.081846, 0.15625, 0.027943,
            0.072678, 0.153293, 0.027943,
            0.072382, 0.139689, 0.027943,
            0.094563, 0.136732, 0.027943,
            0.128573, 0.132591, 0.027943,
            0.170864, 0.120762, 0.027943,
            0.202508, 0.103313, 0.027943,
            0.219365, 0.087934, 0.027943,
            0.237405, 0.065162, 0.027943,
            0.251305, 0.041799, 0.027943,
            0.261952, 0.016661, 0.027943,
            0.268162, -0.004928, 0.027943,
            0.27319, -0.02356, 0.027943,
            0.274373, -0.046332, 0.027943,
            0.274077, -0.072653, 0.027943,
            0.27112, -0.097199, 0.027943,
            0.263431, -0.126182, 0.027943,
            0.252784, -0.152207, 0.027943,
            0.238884, -0.17764, 0.027943,
            0.220253, -0.200708, 0.027943,
            0.200734, -0.220227, 0.027943,
            0.166724, -0.245365, 0.027943,
            0.134784, -0.261039, 0.027943,
            0.102844, -0.272573, 0.027943,
            0.072974, -0.280262, 0.027943,
            0.025655, -0.286177, 0.027943,
            -0.008946, -0.284698, 0.027943,
            -0.033788, -0.279671, 0.027943,
            -0.056856, -0.268433, 0.027943,
            -0.07046, -0.258082, 0.027943,
            -0.081107, -0.246548, 0.027943,
            -0.090275, -0.234127, 0.027943,
            -0.037042, -0.159896, 0.027943,
            -0.024916, -0.166994, 0.027943,
            -0.02462, -0.184147, 0.027943,
            -0.020184, -0.199821, 0.027943,
            -0.011016, -0.215791, 0.027943,
            0.002588, -0.229099, 0.027943,
            0.020036, -0.241816, 0.027943,
            0.038964, -0.248027, 0.027943,
            0.066763, -0.248618, 0.027943,
            0.091014, -0.242703, 0.027943,
            0.114969, -0.230578, 0.027943,
            0.130052, -0.216087, 0.027943,
            0.147205, -0.196568, 0.027943,
            0.161696, -0.170838, 0.027943,
            0.174708, -0.135941, 0.027943,
            0.180328, -0.106367, 0.027943,
            0.183876, -0.077089, 0.027943,
            0.184172, -0.043078, 0.027943,
            0.179736, -0.014983, 0.027943,
            0.172934, 0.008676, 0.027943,
            0.160513, 0.035588, 0.027943,
            0.146317, 0.05422, 0.027943,
            0.129756, 0.070781, 0.027943,
            0.110533, 0.083794, 0.027943,
            0.084212, 0.096511, 0.027943,
            0.060257, 0.105087, 0.027943,
            0.034823, 0.108636, 0.027943,
            -0.060405, 0.108341, 0.027943,
            -0.060405, 0.146195, 0.027943,
            -0.034971, 0.1459, 0.027943,
            -0.010721, 0.149744, 0.027943,
            0.01767, 0.157729, 0.027943,
            0.042808, 0.169263, 0.027943,
            0.072816, 0.189886, 0.027943,
            0.090746, 0.208515, 0.027943,
            0.104059, 0.229229, 0.027943,
            0.111764, 0.249211, 0.027943,
            0.118592, 0.26933, 0.027943,
            0.123634, 0.295385, 0.027943,
            0.121543, 0.32944, 0.027943,
            0.117546, 0.351346, 0.027943,
            0.110801, 0.364503, 0.027943,
            0.102159, 0.383089, 0.027943,
            0.090619, 0.398014, 0.027943,
            0.075526, 0.410997, 0.027943,
            0.058026, 0.422516, 0.027943,
            0.042307, 0.428871, 0.027943,
            0.023302, 0.431857, 0.027943,
            0.00117, 0.432841, 0.027943,
            -0.016631, 0.429134, 0.027943,
            -0.039289, 0.423672, 0.027943,
            -0.057179, 0.413978, 0.027943,
            -0.074665, 0.399807, 0.027943,
            -0.088453, 0.382316, 0.027943,
            -0.097534, 0.367321, 0.027943,
            -0.108611, 0.341337, 0.027943,
            -0.1184, 0.308395, 0.027943,
            -0.126139, 0.263049, 0.027943,
            -0.132028, 0.217263, 0.027943,
            -0.134117, 0.078744, 0.027943,
            -0.131592, -0.218209, 0.027943,
            -0.122652, -0.451308, 0.027943,
            -0.204135, -0.488759, 0.027943,
            -0.216556, -0.472198, 0.027943,
            -0.213303, -0.277009, 0.027943,
            -0.213007, -0.179415, 0.027943,
            -0.211824, -0.069991, 0.027943,
            -0.210937, -0.003745, 0.027943,
            -0.208867, 0.07433, 0.027943,
            -0.206797, 0.13614, 0.027943,
            -0.20236, 0.196471, 0.027943,
            -0.197037, 0.242311, 0.027943,
            -0.190235, 0.278391, 0.027943,
            -0.17811, 0.320682, 0.027943,
            -0.158591, 0.35972, 0.027943,
            -0.132566, 0.396096, 0.027943,
            -0.09826, 0.430697, 0.027943,
            -0.058039, 0.455835, 0.027943,
            -0.011904, 0.473284, 0.027943,
            0.03157, 0.480973, 0.027943,
            0.072087, 0.482156, 0.027943,
            0.104322, 0.475354, 0.027943,
            0.12946, 0.464116, 0.027943,
            0.146613, 0.453765, 0.027943,
            0.162287, 0.440161, 0.027943,
            0.176779, 0.4236, 0.027943,
            0.1892, 0.404672, 0.027943,
            0.197776, 0.383379, 0.027943,
            0.204282, 0.35765, 0.027943,
            0.204874, 0.317429, 0.027943,
            0.198368, 0.290221, 0.027943,
            0.190383, 0.269519, 0.027943,
            0.179736, 0.247043, 0.027943,
            0.16347, 0.222201, 0.027943,
            0.138037, 0.194105, 0.027943,
            0.121771, 0.181093, 0.027943,
            0.102252, 0.16808, 0.027943,
            0.081846, 0.15625, 0.027943,
            0.072678, 0.153293, 0.027943,
            0.072382, 0.139689, 0.027943,
            0.094563, 0.136732, 0.027943,
            0.128573, 0.132591, 0.027943,
            0.170864, 0.120762, 0.027943,
            0.202508, 0.103313, 0.027943,
            0.219365, 0.087934, 0.027943,
            0.237405, 0.065162, 0.027943,
            0.251305, 0.041799, 0.027943,
            0.261952, 0.016661, 0.027943,
            0.268162, -0.004928, 0.027943,
            0.27319, -0.02356, 0.027943,
            0.274373, -0.046332, 0.027943,
            0.274077, -0.072653, 0.027943,
            0.27112, -0.097199, 0.027943,
            0.263431, -0.126182, 0.027943,
            0.252784, -0.152207, 0.027943,
            0.238884, -0.17764, 0.027943,
            0.220253, -0.200708, 0.027943,
            0.200734, -0.220227, 0.027943,
            0.166724, -0.245365, 0.027943,
            0.134784, -0.261039, 0.027943,
            0.102844, -0.272573, 0.027943,
            0.072974, -0.280262, 0.027943,
            0.025655, -0.286177, 0.027943,
            -0.008946, -0.284698, 0.027943,
            -0.033788, -0.279671, 0.027943,
            -0.056856, -0.268433, 0.027943,
            -0.07046, -0.258082, 0.027943,
            -0.081107, -0.246548, 0.027943,
            -0.090275, -0.234127, 0.027943,
            -0.037042, -0.159896, 0.027943,
            -0.024916, -0.166994, 0.027943,
            -0.02462, -0.184147, 0.027943,
            -0.020184, -0.199821, 0.027943,
            -0.011016, -0.215791, 0.027943,
            0.002588, -0.229099, 0.027943,
            0.020036, -0.241816, 0.027943,
            0.038964, -0.248027, 0.027943,
            0.066763, -0.248618, 0.027943,
            0.091014, -0.242703, 0.027943,
            0.114969, -0.230578, 0.027943,
            0.130052, -0.216087, 0.027943,
            0.147205, -0.196568, 0.027943,
            0.161696, -0.170838, 0.027943,
            0.174708, -0.135941, 0.027943,
            0.180328, -0.106367, 0.027943,
            0.183876, -0.077089, 0.027943,
            0.184172, -0.043078, 0.027943,
            0.179736, -0.014983, 0.027943,
            0.172934, 0.008676, 0.027943,
            0.160513, 0.035588, 0.027943,
            0.146317, 0.05422, 0.027943,
            0.129756, 0.070781, 0.027943,
            0.110533, 0.083794, 0.027943,
            0.084212, 0.096511, 0.027943,
            0.060257, 0.105087, 0.027943,
            0.034823, 0.108636, 0.027943,
            -0.060405, 0.108341, 0.027943,
            -0.060405, 0.146195, 0.027943,
            -0.034971, 0.1459, 0.027943,
            -0.010721, 0.149744, 0.027943,
            0.01767, 0.157729, 0.027943,
            0.042808, 0.169263, 0.027943,
            0.072816, 0.189886, 0.027943,
            0.090746, 0.208515, 0.027943,
            0.104059, 0.229229, 0.027943,
            0.111764, 0.249211, 0.027943,
            0.118592, 0.26933, 0.027943,
            0.123634, 0.295385, 0.027943,
            0.121543, 0.32944, 0.027943,
            0.117546, 0.351346, 0.027943,
            0.110801, 0.364503, 0.027943,
            0.102159, 0.383089, 0.027943,
            0.090619, 0.398014, 0.027943,
            0.075526, 0.410997, 0.027943,
            0.058026, 0.422516, 0.027943,
            0.042307, 0.428871, 0.027943,
            0.023302, 0.431857, 0.027943,
            0.00117, 0.432841, 0.027943,
            -0.016631, 0.429134, 0.027943,
            -0.039289, 0.423672, 0.027943,
            -0.057179, 0.413978, 0.027943,
            -0.074665, 0.399807, 0.027943,
            -0.088453, 0.382316, 0.027943,
            -0.097534, 0.367321, 0.027943,
            -0.108611, 0.341337, 0.027943,
            -0.1184, 0.308395, 0.027943,
            -0.126139, 0.263049, 0.027943,
            -0.132028, 0.217263, 0.027943,
            -0.134117, 0.078744, 0.027943,
            -0.131592, -0.218209, 0.027943,
            -0.122652, -0.451308, 0.027943,
            -0.204135, -0.488759, 0.027943,
            -0.216556, -0.472198, 0.027943,
            -0.213303, -0.277009, 0.027943,
            -0.213007, -0.179415, 0.027943,
            -0.211824, -0.069991, 0.027943,
            -0.210937, -0.003745, 0.027943,
            -0.208867, 0.07433, 0.027943,
            -0.206797, 0.13614, 0.027943,
            -0.20236, 0.196471, 0.027943,
            -0.197037, 0.242311, 0.027943,
            -0.190235, 0.278391, 0.027943,
            -0.17811, 0.320682, 0.027943,
            -0.158591, 0.35972, 0.027943,
            -0.132566, 0.396096, 0.027943,
            -0.09826, 0.430697, 0.027943,
            -0.058039, 0.455835, 0.027943,
            -0.011904, 0.473284, 0.027943,
            0.03157, 0.480973, 0.027943,
            0.072087, 0.482156, 0.027943,
            0.104322, 0.475354, 0.027943,
            0.12946, 0.464116, 0.027943,
            0.146613, 0.453765, 0.027943,
            0.162287, 0.440161, 0.027943,
            0.176779, 0.4236, 0.027943,
            0.1892, 0.404672, 0.027943,
            0.197776, 0.383379, 0.027943,
            0.204282, 0.35765, 0.027943,
            0.204874, 0.317429, 0.027943,
            0.198368, 0.290221, 0.027943,
            0.190383, 0.269519, 0.027943,
            0.179736, 0.247043, 0.027943,
            0.16347, 0.222201, 0.027943,
            0.138037, 0.194105, 0.027943,
            0.121771, 0.181093, 0.027943,
            0.102252, 0.16808, 0.027943,
            0.081846, 0.15625, 0.027943,
            0.072678, 0.153293, 0.027943,
            0.072382, 0.139689, 0.027943,
            0.094563, 0.136732, 0.027943,
            0.128573, 0.132591, 0.027943,
            0.170864, 0.120762, 0.027943,
            0.202508, 0.103313, 0.027943,
            0.219365, 0.087934, 0.027943,
            0.237405, 0.065162, 0.027943,
            0.251305, 0.041799, 0.027943,
            0.261952, 0.016661, 0.027943,
            0.268162, -0.004928, 0.027943,
            0.27319, -0.02356, 0.027943,
            0.274373, -0.046332, 0.027943,
            0.274077, -0.072653, 0.027943,
            0.27112, -0.097199, 0.027943,
            0.263431, -0.126182, 0.027943,
            0.252784, -0.152207, 0.027943,
            0.238884, -0.17764, 0.027943,
            0.220253, -0.200708, 0.027943,
            0.200734, -0.220227, 0.027943,
            0.166724, -0.245365, 0.027943,
            0.134784, -0.261039, 0.027943,
            0.102844, -0.272573, 0.027943,
            0.072974, -0.280262, 0.027943,
            0.025655, -0.286177, 0.027943,
            -0.008946, -0.284698, 0.027943,
            -0.033788, -0.279671, 0.027943,
            -0.056856, -0.268433, 0.027943,
            -0.07046, -0.258082, 0.027943,
            -0.081107, -0.246548, 0.027943,
            -0.090275, -0.234127, 0.027943,
            -0.037042, -0.159896, 0.027943,
            -0.024916, -0.166994, 0.027943,
            -0.02462, -0.184147, 0.027943,
            -0.020184, -0.199821, 0.027943,
            -0.011016, -0.215791, 0.027943,
            0.002588, -0.229099, 0.027943,
            0.020036, -0.241816, 0.027943,
            0.038964, -0.248027, 0.027943,
            0.066763, -0.248618, 0.027943,
            0.091014, -0.242703, 0.027943,
            0.114969, -0.230578, 0.027943,
            0.130052, -0.216087, 0.027943,
            0.147205, -0.196568, 0.027943,
            0.161696, -0.170838, 0.027943,
            0.174708, -0.135941, 0.027943,
            0.180328, -0.106367, 0.027943,
            0.183876, -0.077089, 0.027943,
            0.184172, -0.043078, 0.027943,
            0.179736, -0.014983, 0.027943,
            0.172934, 0.008676, 0.027943,
            0.160513, 0.035588, 0.027943,
            0.146317, 0.05422, 0.027943,
            0.129756, 0.070781, 0.027943,
            0.110533, 0.083794, 0.027943,
            0.084212, 0.096511, 0.027943,
            0.060257, 0.105087, 0.027943,
            0.034823, 0.108636, 0.027943,
            -0.060405, 0.108341, 0.027943,
            -0.060405, 0.146195, 0.027943,
            -0.034971, 0.1459, 0.027943,
            -0.010721, 0.149744, 0.027943,
            0.01767, 0.157729, 0.027943,
            0.042808, 0.169263, 0.027943,
            0.072816, 0.189886, 0.027943,
            0.090746, 0.208515, 0.027943,
            0.104059, 0.229229, 0.027943,
            0.111764, 0.249211, 0.027943,
            0.118592, 0.26933, 0.027943,
            0.123634, 0.295385, 0.027943,
            0.121543, 0.32944, 0.027943,
            0.117546, 0.351346, 0.027943,
            0.110801, 0.364503, 0.027943,
            0.102159, 0.383089, 0.027943,
            0.090619, 0.398014, 0.027943,
            0.075526, 0.410997, 0.027943,
            0.058026, 0.422516, 0.027943,
            0.042307, 0.428871, 0.027943,
            0.023302, 0.431857, 0.027943,
            0.00117, 0.432841, 0.027943,
            -0.016631, 0.429134, 0.027943,
            -0.039289, 0.423672, 0.027943,
            -0.057179, 0.413978, 0.027943,
            -0.074665, 0.399807, 0.027943,
            -0.088453, 0.382316, 0.027943,
            -0.097534, 0.367321, 0.027943,
            -0.108611, 0.341337, 0.027943,
            -0.1184, 0.308395, 0.027943,
            -0.126139, 0.263049, 0.027943,
            -0.132028, 0.217263, 0.027943,
            -0.134117, 0.078744, 0.027943,
            -0.131592, -0.218209, 0.027943,
            -0.122652, -0.451308, 0.027943,
            0.104322, 0.475354, -0.029529,
            0.058026, 0.422516, -0.029529,
            0.072087, 0.482156, -0.029529,
            0.162287, 0.440161, -0.029529,
            0.176779, 0.4236, -0.029529,
            0.102159, 0.383089, -0.029529,
            0.12946, 0.464116, -0.029529,
            0.075526, 0.410997, -0.029529,
            0.104322, 0.475354, -0.029529,
            0.00117, 0.432841, -0.029529,
            -0.011904, 0.473284, -0.029529,
            0.03157, 0.480973, -0.029529,
            0.042307, 0.428871, -0.029529,
            0.023302, 0.431857, -0.029529,
            0.03157, 0.480973, -0.029529,
            -0.058039, 0.455835, -0.029529,
            -0.039289, 0.423672, -0.029529,
            -0.057179, 0.413978, -0.029529,
            0.002588, -0.229099, -0.029529,
            0.020036, -0.241816, -0.029529,
            -0.008946, -0.284698, -0.029529,
            -0.058039, 0.455835, -0.029529,
            -0.016631, 0.429134, -0.029529,
            -0.039289, 0.423672, -0.029529,
            0.023302, 0.431857, -0.029529,
            0.00117, 0.432841, -0.029529,
            0.03157, 0.480973, -0.029529,
            0.146613, 0.453765, -0.029529,
            0.090619, 0.398014, -0.029529,
            0.12946, 0.464116, -0.029529,
            -0.011904, 0.473284, -0.029529,
            0.00117, 0.432841, -0.029529,
            -0.016631, 0.429134, -0.029529,
            0.090619, 0.398014, -0.029529,
            0.075526, 0.410997, -0.029529,
            0.12946, 0.464116, -0.029529,
            -0.09826, 0.430697, -0.029529,
            -0.058039, 0.455835, -0.029529,
            -0.057179, 0.413978, -0.029529,
            0.197776, 0.383379, -0.029529,
            0.204282, 0.35765, -0.029529,
            0.117546, 0.351346, -0.029529,
            0.058026, 0.422516, -0.029529,
            0.042307, 0.428871, -0.029529,
            0.072087, 0.482156, -0.029529,
            -0.09826, 0.430697, -0.029529,
            -0.057179, 0.413978, -0.029529,
            -0.074665, 0.399807, -0.029529,
            0.219365, 0.087934, -0.029529,
            0.160513, 0.035588, -0.029529,
            0.202508, 0.103313, -0.029529,
            0.1892, 0.404672, -0.029529,
            0.110801, 0.364503, -0.029529,
            0.176779, 0.4236, -0.029529,
            0.134784, -0.261039, -0.029529,
            0.114969, -0.230578, -0.029529,
            0.130052, -0.216087, -0.029529,
            0.102844, -0.272573, -0.029529,
            0.091014, -0.242703, -0.029529,
            0.114969, -0.230578, -0.029529,
            0.172934, 0.008676, -0.029529,
            0.160513, 0.035588, -0.029529,
            0.237405, 0.065162, -0.029529,
            -0.132566, 0.396096, -0.029529,
            -0.09826, 0.430697, -0.029529,
            -0.088453, 0.382316, -0.029529,
            0.110801, 0.364503, -0.029529,
            0.102159, 0.383089, -0.029529,
            0.176779, 0.4236, -0.029529,
            -0.088453, 0.382316, -0.029529,
            -0.097534, 0.367321, -0.029529,
            -0.132566, 0.396096, -0.029529,
            0.042808, 0.169263, -0.029529,
            0.072382, 0.139689, -0.029529,
            0.034823, 0.108636, -0.029529,
            0.161696, -0.170838, -0.029529,
            0.220253, -0.200708, -0.029529,
            0.200734, -0.220227, -0.029529,
            0.042808, 0.169263, -0.029529,
            0.072678, 0.153293, -0.029529,
            0.072382, 0.139689, -0.029529,
            -0.158591, 0.35972, -0.029529,
            -0.097534, 0.367321, -0.029529,
            -0.108611, 0.341337, -0.029529,
            0.110801, 0.364503, -0.029529,
            0.1892, 0.404672, -0.029529,
            0.117546, 0.351346, -0.029529,
            -0.108611, 0.341337, -0.029529,
            -0.1184, 0.308395, -0.029529,
            -0.158591, 0.35972, -0.029529,
            0.204874, 0.317429, -0.029529,
            0.121543, 0.32944, -0.029529,
            0.204282, 0.35765, -0.029529,
            0.16347, 0.222201, -0.029529,
            0.111764, 0.249211, -0.029529,
            0.118592, 0.26933, -0.029529,
            -0.09826, 0.430697, -0.029529,
            -0.074665, 0.399807, -0.029529,
            -0.088453, 0.382316, -0.029529,
            0.123634, 0.295385, -0.029529,
            0.121543, 0.32944, -0.029529,
            0.204874, 0.317429, -0.029529,
            -0.1184, 0.308395, -0.029529,
            -0.126139, 0.263049, -0.029529,
            -0.17811, 0.320682, -0.029529,
            0.123634, 0.295385, -0.029529,
            0.204874, 0.317429, -0.029529,
            0.198368, 0.290221, -0.029529,
            0.1892, 0.404672, -0.029529,
            0.197776, 0.383379, -0.029529,
            0.117546, 0.351346, -0.029529,
            0.198368, 0.290221, -0.029529,
            0.190383, 0.269519, -0.029529,
            0.123634, 0.295385, -0.029529,
            0.090746, 0.208515, -0.029529,
            0.121771, 0.181093, -0.029529,
            0.102252, 0.16808, -0.029529,
            -0.197037, 0.242311, -0.029529,
            -0.190235, 0.278391, -0.029529,
            -0.126139, 0.263049, -0.029529,
            0.118592, 0.26933, -0.029529,
            0.190383, 0.269519, -0.029529,
            0.179736, 0.247043, -0.029529,
            0.179736, 0.247043, -0.029529,
            0.16347, 0.222201, -0.029529,
            0.118592, 0.26933, -0.029529,
            -0.197037, 0.242311, -0.029529,
            -0.126139, 0.263049, -0.029529,
            -0.132028, 0.217263, -0.029529,
            0.184172, -0.043078, -0.029529,
            0.179736, -0.014983, -0.029529,
            0.268162, -0.004928, -0.029529,
            -0.02462, -0.184147, -0.029529,
            -0.090275, -0.234127, -0.029529,
            -0.037042, -0.159896, -0.029529,
            -0.20236, 0.196471, -0.029529,
            -0.197037, 0.242311, -0.029529,
            -0.132028, 0.217263, -0.029529,
            0.16347, 0.222201, -0.029529,
            0.138037, 0.194105, -0.029529,
            0.104059, 0.229229, -0.029529,
            0.01767, 0.157729, -0.029529,
            0.042808, 0.169263, -0.029529,
            0.034823, 0.108636, -0.029529,
            -0.134117, 0.078744, -0.029529,
            -0.206797, 0.13614, -0.029529,
            -0.132028, 0.217263, -0.029529,
            0.138037, 0.194105, -0.029529,
            0.121771, 0.181093, -0.029529,
            0.090746, 0.208515, -0.029529,
            -0.07046, -0.258082, -0.029529,
            -0.011016, -0.215791, -0.029529,
            -0.056856, -0.268433, -0.029529,
            -0.058039, 0.455835, -0.029529,
            -0.011904, 0.473284, -0.029529,
            -0.016631, 0.429134, -0.029529,
            0.072816, 0.189886, -0.029529,
            0.090746, 0.208515, -0.029529,
            0.102252, 0.16808, -0.029529,
            -0.081107, -0.246548, -0.029529,
            -0.090275, -0.234127, -0.029529,
            -0.020184, -0.199821, -0.029529,
            -0.206797, 0.13614, -0.029529,
            -0.20236, 0.196471, -0.029529,
            -0.132028, 0.217263, -0.029529,
            0.081846, 0.15625, -0.029529,
            0.072678, 0.153293, -0.029529,
            0.072816, 0.189886, -0.029529,
            0.072678, 0.153293, -0.029529,
            0.042808, 0.169263, -0.029529,
            0.072816, 0.189886, -0.029529,
            0.179736, -0.014983, -0.029529,
            0.172934, 0.008676, -0.029529,
            0.261952, 0.016661, -0.029529,
            -0.010721, 0.149744, -0.029529,
            0.01767, 0.157729, -0.029529,
            0.034823, 0.108636, -0.029529,
            -0.060405, 0.108341, -0.029529,
            -0.060405, 0.146195, -0.029529,
            -0.034971, 0.1459, -0.029529,
            0.166724, -0.245365, -0.029529,
            0.134784, -0.261039, -0.029529,
            0.130052, -0.216087, -0.029529,
            0.094563, 0.136732, -0.029529,
            0.084212, 0.096511, -0.029529,
            0.072382, 0.139689, -0.029529,
            0.128573, 0.132591, -0.029529,
            0.110533, 0.083794, -0.029529,
            0.094563, 0.136732, -0.029529,
            -0.208867, 0.07433, -0.029529,
            -0.206797, 0.13614, -0.029529,
            -0.134117, 0.078744, -0.029529,
            0.170864, 0.120762, -0.029529,
            0.129756, 0.070781, -0.029529,
            0.128573, 0.132591, -0.029529,
            -0.034971, 0.1459, -0.029529,
            -0.010721, 0.149744, -0.029529,
            -0.060405, 0.108341, -0.029529,
            0.146613, 0.453765, -0.029529,
            0.162287, 0.440161, -0.029529,
            0.090619, 0.398014, -0.029529,
            0.060257, 0.105087, -0.029529,
            0.034823, 0.108636, -0.029529,
            0.072382, 0.139689, -0.029529,
            0.072974, -0.280262, -0.029529,
            0.066763, -0.248618, -0.029529,
            0.091014, -0.242703, -0.029529,
            0.075526, 0.410997, -0.029529,
            0.058026, 0.422516, -0.029529,
            0.104322, 0.475354, -0.029529,
            0.16347, 0.222201, -0.029529,
            0.104059, 0.229229, -0.029529,
            0.111764, 0.249211, -0.029529,
            0.147205, -0.196568, -0.029529,
            0.200734, -0.220227, -0.029529,
            0.166724, -0.245365, -0.029529,
            0.237405, 0.065162, -0.029529,
            0.160513, 0.035588, -0.029529,
            0.219365, 0.087934, -0.029529,
            0.252784, -0.152207, -0.029529,
            0.174708, -0.135941, -0.029529,
            0.180328, -0.106367, -0.029529,
            0.102252, 0.16808, -0.029529,
            0.081846, 0.15625, -0.029529,
            0.072816, 0.189886, -0.029529,
            0.121543, 0.32944, -0.029529,
            0.117546, 0.351346, -0.029529,
            0.204282, 0.35765, -0.029529,
            0.251305, 0.041799, -0.029529,
            0.172934, 0.008676, -0.029529,
            0.237405, 0.065162, -0.029529,
            0.072087, 0.482156, -0.029529,
            0.042307, 0.428871, -0.029529,
            0.03157, 0.480973, -0.029529,
            0.261952, 0.016661, -0.029529,
            0.172934, 0.008676, -0.029529,
            0.251305, 0.041799, -0.029529,
            0.274077, -0.072653, -0.029529,
            0.183876, -0.077089, -0.029529,
            0.184172, -0.043078, -0.029529,
            0.268162, -0.004928, -0.029529,
            0.179736, -0.014983, -0.029529,
            0.261952, 0.016661, -0.029529,
            0.129756, 0.070781, -0.029529,
            0.110533, 0.083794, -0.029529,
            0.128573, 0.132591, -0.029529,
            -0.210937, -0.003745, -0.029529,
            -0.134117, 0.078744, -0.029529,
            -0.211824, -0.069991, -0.029529,
            0.27319, -0.02356, -0.029529,
            0.184172, -0.043078, -0.029529,
            0.268162, -0.004928, -0.029529,
            0.110533, 0.083794, -0.029529,
            0.084212, 0.096511, -0.029529,
            0.094563, 0.136732, -0.029529,
            0.184172, -0.043078, -0.029529,
            0.27319, -0.02356, -0.029529,
            0.274373, -0.046332, -0.029529,
            0.274373, -0.046332, -0.029529,
            0.274077, -0.072653, -0.029529,
            0.184172, -0.043078, -0.029529,
            0.160513, 0.035588, -0.029529,
            0.146317, 0.05422, -0.029529,
            0.202508, 0.103313, -0.029529,
            -0.213007, -0.179415, -0.029529,
            -0.211824, -0.069991, -0.029529,
            -0.131592, -0.218209, -0.029529,
            0.183876, -0.077089, -0.029529,
            0.274077, -0.072653, -0.029529,
            0.27112, -0.097199, -0.029529,
            0.180328, -0.106367, -0.029529,
            0.183876, -0.077089, -0.029529,
            0.27112, -0.097199, -0.029529,
            0.180328, -0.106367, -0.029529,
            0.27112, -0.097199, -0.029529,
            0.263431, -0.126182, -0.029529,
            0.263431, -0.126182, -0.029529,
            0.252784, -0.152207, -0.029529,
            0.180328, -0.106367, -0.029529,
            -0.010721, 0.149744, -0.029529,
            0.034823, 0.108636, -0.029529,
            -0.060405, 0.108341, -0.029529,
            0.252784, -0.152207, -0.029529,
            0.238884, -0.17764, -0.029529,
            0.174708, -0.135941, -0.029529,
            -0.126139, 0.263049, -0.029529,
            -0.190235, 0.278391, -0.029529,
            -0.17811, 0.320682, -0.029529,
            -0.024916, -0.166994, -0.029529,
            -0.02462, -0.184147, -0.029529,
            -0.037042, -0.159896, -0.029529,
            0.238884, -0.17764, -0.029529,
            0.161696, -0.170838, -0.029529,
            0.174708, -0.135941, -0.029529,
            0.238884, -0.17764, -0.029529,
            0.220253, -0.200708, -0.029529,
            0.161696, -0.170838, -0.029529,
            -0.097534, 0.367321, -0.029529,
            -0.158591, 0.35972, -0.029529,
            -0.132566, 0.396096, -0.029529,
            -0.213303, -0.277009, -0.029529,
            -0.213007, -0.179415, -0.029529,
            -0.131592, -0.218209, -0.029529,
            -0.090275, -0.234127, -0.029529,
            -0.02462, -0.184147, -0.029529,
            -0.020184, -0.199821, -0.029529,
            0.147205, -0.196568, -0.029529,
            0.161696, -0.170838, -0.029529,
            0.200734, -0.220227, -0.029529,
            -0.011016, -0.215791, -0.029529,
            -0.081107, -0.246548, -0.029529,
            -0.020184, -0.199821, -0.029529,
            0.084212, 0.096511, -0.029529,
            0.060257, 0.105087, -0.029529,
            0.072382, 0.139689, -0.029529,
            -0.1184, 0.308395, -0.029529,
            -0.17811, 0.320682, -0.029529,
            -0.158591, 0.35972, -0.029529,
            0.130052, -0.216087, -0.029529,
            0.147205, -0.196568, -0.029529,
            0.166724, -0.245365, -0.029529,
            -0.213303, -0.277009, -0.029529,
            -0.131592, -0.218209, -0.029529,
            -0.122652, -0.451308, -0.029529,
            -0.134117, 0.078744, -0.029529,
            -0.131592, -0.218209, -0.029529,
            -0.211824, -0.069991, -0.029529,
            0.090619, 0.398014, -0.029529,
            0.162287, 0.440161, -0.029529,
            0.102159, 0.383089, -0.029529,
            0.146317, 0.05422, -0.029529,
            0.129756, 0.070781, -0.029529,
            0.170864, 0.120762, -0.029529,
            0.038964, -0.248027, -0.029529,
            0.066763, -0.248618, -0.029529,
            0.072974, -0.280262, -0.029529,
            0.020036, -0.241816, -0.029529,
            0.038964, -0.248027, -0.029529,
            0.025655, -0.286177, -0.029529,
            0.138037, 0.194105, -0.029529,
            0.090746, 0.208515, -0.029529,
            0.104059, 0.229229, -0.029529,
            0.134784, -0.261039, -0.029529,
            0.102844, -0.272573, -0.029529,
            0.114969, -0.230578, -0.029529,
            -0.081107, -0.246548, -0.029529,
            -0.011016, -0.215791, -0.029529,
            -0.07046, -0.258082, -0.029529,
            0.190383, 0.269519, -0.029529,
            0.118592, 0.26933, -0.029529,
            0.123634, 0.295385, -0.029529,
            0.102844, -0.272573, -0.029529,
            0.072974, -0.280262, -0.029529,
            0.091014, -0.242703, -0.029529,
            0.202508, 0.103313, -0.029529,
            0.146317, 0.05422, -0.029529,
            0.170864, 0.120762, -0.029529,
            -0.011016, -0.215791, -0.029529,
            0.002588, -0.229099, -0.029529,
            -0.033788, -0.279671, -0.029529,
            -0.056856, -0.268433, -0.029529,
            -0.011016, -0.215791, -0.029529,
            -0.033788, -0.279671, -0.029529,
            0.025655, -0.286177, -0.029529,
            0.038964, -0.248027, -0.029529,
            0.072974, -0.280262, -0.029529,
            -0.216556, -0.472198, -0.029529,
            -0.213303, -0.277009, -0.029529,
            -0.122652, -0.451308, -0.029529,
            -0.033788, -0.279671, -0.029529,
            0.002588, -0.229099, -0.029529,
            -0.008946, -0.284698, -0.029529,
            -0.008946, -0.284698, -0.029529,
            0.020036, -0.241816, -0.029529,
            0.025655, -0.286177, -0.029529,
            -0.216556, -0.472198, -0.029529,
            -0.122652, -0.451308, -0.029529,
            -0.204135, -0.488759, -0.029529,
            -0.210937, -0.003745, -0.029529,
            -0.208867, 0.07433, -0.029529,
            -0.134117, 0.078744, -0.029529
    };

    unsigned int indices_beta[] = {
            19, 18, 112, 22, 109, 23, 20, 19, 111, 115, 17, 16, 113, 17, 114, 15, 118, 117, 72, 61, 73, 15, 117,
            116,
            114, 17, 115, 21, 20, 110, 16, 116, 115, 110, 20, 111, 14, 118, 15, 25, 107, 26, 112, 18, 113, 14, 119,
            118,
            42, 41, 87, 24, 23, 108, 57, 78, 77, 58, 77, 76, 86, 43, 87, 13, 120, 14, 108, 23, 109, 120, 13, 121,
            99,
            93, 37, 80, 55, 54, 99, 37, 36, 12, 122, 121, 108, 107, 24, 122, 12, 123, 27, 26, 106, 31, 104, 103, 14,
            120, 119, 105, 27, 106, 123, 11, 124, 105, 28, 27, 24, 107, 25, 28, 105, 29, 101, 34, 33, 9, 124, 10,
            104,
            30, 29, 30, 104, 31, 9, 125, 124, 84, 46, 85, 69, 67, 66, 8, 125, 9, 31, 102, 32, 98, 93, 99, 126, 125,
            7,
            32, 101, 33, 64, 63, 71, 15, 116, 16, 100, 34, 101, 65, 70, 66, 7, 125, 8, 35, 100, 36, 36, 100, 99,
            221,
            351, 350, 85, 45, 86, 97, 93, 98, 94, 96, 95, 56, 78, 57, 38, 37, 91, 39, 38, 90, 6, 126, 7, 40, 39, 89,
            96,
            94, 97, 21, 110, 22, 92, 37, 93, 59, 76, 75, 111, 19, 112, 31, 103, 102, 79, 56, 55, 43, 42, 87, 52, 82,
            81,
            34, 100, 35, 106, 26, 107, 44, 43, 86, 18, 17, 113, 45, 44, 86, 49, 84, 83, 46, 45, 85, 89, 39, 90, 5,
            4,
            126, 47, 46, 84, 90, 38, 91, 84, 48, 47, 48, 84, 49, 87, 41, 88, 3, 127, 4, 83, 50, 49, 82, 50, 83, 82,
            51,
            50, 51, 82, 52, 97, 94, 93, 52, 81, 53, 124, 11, 10, 68, 67, 69, 53, 81, 80, 53, 80, 54, 121, 13, 12, 2,
            127, 3, 66, 70, 69, 79, 55, 80, 71, 70, 65, 91, 37, 92, 123, 12, 11, 78, 56, 79, 2, 128, 127, 126, 4,
            127,
            110, 109, 22, 88, 40, 89, 74, 59, 75, 73, 60, 74, 32, 102, 101, 57, 77, 58, 65, 64, 71, 29, 105, 104,
            58,
            76, 59, 41, 40, 88, 71, 62, 72, 63, 62, 71, 60, 59, 74, 1, 128, 2, 62, 61, 72, 61, 60, 73, 1, 0, 128, 5,
            126, 6, 169, 299, 298, 220, 350, 349, 168, 298, 297, 219, 349, 348, 167, 297, 296, 218, 348, 347, 166,
            296,
            295, 217, 347, 346, 165, 295, 294, 216, 346, 345, 164, 294, 293, 215, 345, 344, 163, 293, 292, 129, 259,
            258, 214, 344, 343, 162, 292, 291, 213, 343, 342, 161, 291, 290, 212, 342, 341, 160, 290, 289, 211, 341,
            340, 159, 289, 288, 210, 340, 339, 158, 288, 287, 209, 339, 338, 157, 287, 286, 208, 338, 337, 156, 286,
            285, 207, 337, 336, 155, 285, 284, 206, 336, 335, 257, 258, 386, 154, 284, 283, 205, 335, 334, 256, 386,
            385, 153, 283, 282, 204, 334, 333, 255, 385, 384, 152, 282, 281, 203, 333, 332, 254, 384, 383, 151, 281,
            280, 202, 332, 331, 253, 383, 382, 150, 280, 279, 201, 331, 330, 252, 382, 381, 149, 279, 278, 200, 330,
            329, 251, 381, 380, 148, 278, 277, 199, 329, 328, 250, 380, 379, 147, 277, 276, 198, 328, 327, 249, 379,
            378, 146, 276, 275, 197, 327, 326, 248, 378, 377, 145, 275, 274, 196, 326, 325, 247, 377, 376, 144, 274,
            273, 195, 325, 324, 246, 376, 375, 143, 273, 272, 194, 324, 323, 245, 375, 374, 142, 272, 271, 193, 323,
            322, 244, 374, 373, 141, 271, 270, 192, 322, 321, 243, 373, 372, 140, 270, 269, 191, 321, 320, 242, 372,
            371, 139, 269, 268, 190, 320, 319, 241, 371, 370, 138, 268, 267, 189, 319, 318, 240, 370, 369, 137, 267,
            266, 188, 318, 317, 239, 369, 368, 136, 266, 265, 187, 317, 316, 238, 368, 367, 135, 265, 264, 186, 316,
            315, 237, 367, 366, 134, 264, 263, 185, 315, 314, 236, 366, 365, 133, 263, 262, 184, 314, 313, 235, 365,
            364, 132, 262, 261, 183, 313, 312, 234, 364, 363, 131, 261, 260, 182, 312, 311, 233, 363, 362, 130, 260,
            259, 181, 311, 310, 232, 362, 361, 180, 310, 309, 231, 361, 360, 179, 309, 308, 230, 360, 359, 178, 308,
            307, 229, 359, 358, 177, 307, 306, 228, 358, 357, 176, 306, 305, 227, 357, 356, 175, 305, 304, 226, 356,
            355, 174, 304, 303, 225, 355, 354, 173, 303, 302, 224, 354, 353, 172, 302, 301, 223, 353, 352, 171, 301,
            300, 51, 181, 180, 0, 130, 129, 103, 233, 232, 52, 182, 181, 1, 131, 130, 104, 234, 233, 53, 183, 182,
            2,
            132, 131, 105, 235, 234, 54, 184, 183, 3, 133, 132, 106, 236, 235, 55, 185, 184, 4, 134, 133, 107, 237,
            236,
            56, 186, 185, 5, 135, 134, 108, 238, 237, 57, 187, 186, 6, 136, 135, 109, 239, 238, 58, 188, 187, 7,
            137,
            136, 110, 240, 239, 59, 189, 188, 8, 138, 137, 111, 241, 240, 60, 190, 189, 9, 139, 138, 112, 242, 241,
            61,
            191, 190, 10, 140, 139, 113, 243, 242, 62, 192, 191, 11, 141, 140, 114, 244, 243, 63, 193, 192, 12, 142,
            141, 115, 245, 244, 64, 194, 193, 13, 143, 142, 116, 246, 245, 65, 195, 194, 14, 144, 143, 117, 247,
            246,
            66, 196, 195, 15, 145, 144, 118, 248, 247, 67, 197, 196, 16, 146, 145, 119, 249, 248, 68, 198, 197, 17,
            147,
            146, 120, 250, 249, 69, 199, 198, 18, 148, 147, 121, 251, 250, 70, 200, 199, 19, 149, 148, 122, 252,
            251,
            71, 201, 200, 20, 150, 149, 123, 253, 252, 72, 202, 201, 21, 151, 150, 124, 254, 253, 73, 203, 202, 22,
            152,
            151, 125, 255, 254, 74, 204, 203, 23, 153, 152, 126, 256, 255, 75, 205, 204, 24, 154, 153, 127, 257,
            256,
            76, 206, 205, 25, 155, 154, 128, 129, 257, 77, 207, 206, 26, 156, 155, 78, 208, 207, 27, 157, 156, 79,
            209,
            208, 28, 158, 157, 80, 210, 209, 29, 159, 158, 81, 211, 210, 30, 160, 159, 82, 212, 211, 31, 161, 160,
            83,
            213, 212, 32, 162, 161, 84, 214, 213, 33, 163, 162, 85, 215, 214, 34, 164, 163, 86, 216, 215, 35, 165,
            164,
            87, 217, 216, 36, 166, 165, 88, 218, 217, 37, 167, 166, 89, 219, 218, 38, 168, 167, 90, 220, 219, 39,
            169,
            168, 91, 221, 220, 40, 170, 169, 92, 222, 221, 41, 171, 170, 93, 223, 222, 42, 172, 171, 94, 224, 223,
            43,
            173, 172, 95, 225, 224, 44, 174, 173, 96, 226, 225, 45, 175, 174, 97, 227, 226, 46, 176, 175, 98, 228,
            227,
            47, 177, 176, 99, 229, 228, 48, 178, 177, 100, 230, 229, 49, 179, 178, 101, 231, 230, 50, 180, 179, 102,
            232, 231, 170, 300, 299, 222, 352, 351, 387, 388, 389, 388, 277, 370, 389, 370, 276, 390, 391, 392, 392,
            281, 367, 390, 367, 280, 393, 394, 395, 394, 278, 369, 395, 369, 277, 396, 397, 398, 397, 373, 274, 396,
            275, 373, 399, 400, 401, 401, 372, 275, 399, 275, 371, 402, 403, 404, 403, 273, 375, 402, 376, 273, 405,
            406, 407, 407, 331, 319, 405, 319, 330, 408, 409, 410, 409, 273, 374, 408, 375, 273, 411, 412, 413, 413,
            373, 275, 411, 275, 372, 414, 415, 416, 415, 279, 368, 416, 368, 278, 417, 418, 419, 418, 274, 373, 417,
            374, 274, 420, 421, 422, 422, 369, 278, 420, 278, 368, 423, 424, 425, 425, 273, 376, 423, 376, 272, 426,
            427, 428, 428, 284, 365, 426, 365, 283, 429, 430, 431, 431, 371, 276, 429, 276, 370, 432, 433, 434, 433,
            272, 376, 432, 377, 272, 435, 436, 437, 436, 300, 345, 437, 345, 299, 438, 439, 440, 439, 282, 366, 440,
            366, 281, 441, 442, 443, 442, 315, 335, 441, 336, 315, 444, 445, 446, 445, 316, 334, 444, 335, 316, 447,
            448, 449, 449, 345, 301, 447, 301, 344, 450, 451, 452, 452, 272, 378, 450, 378, 271, 453, 454, 455, 455,
            367, 281, 453, 281, 366, 456, 457, 458, 458, 379, 271, 456, 271, 378, 459, 460, 461, 460, 357, 295, 461,
            295, 351, 459, 351, 357, 462, 463, 464, 463, 338, 312, 462, 313, 338, 465, 466, 467, 466, 357, 294, 465,
            295, 357, 468, 469, 470, 469, 270, 379, 468, 380, 270, 471, 472, 473, 472, 366, 282, 473, 282, 365, 474,
            475, 476, 476, 381, 270, 474, 270, 380, 477, 478, 479, 478, 285, 364, 479, 364, 284, 480, 481, 482, 481,
            289, 361, 480, 362, 289, 483, 484, 485, 484, 272, 377, 483, 378, 272, 486, 487, 488, 488, 364, 285, 486,
            285, 363, 489, 490, 491, 491, 382, 269, 489, 269, 381, 492, 493, 494, 493, 363, 285, 492, 286, 363, 495,
            496, 497, 497, 283, 365, 495, 365, 282, 498, 499, 500, 500, 287, 363, 498, 363, 286, 501, 502, 503, 502,
            359, 291, 501, 292, 359, 504, 505, 506, 506, 268, 382, 504, 382, 267, 507, 508, 509, 508, 362, 287, 507,
            288, 362, 510, 511, 512, 512, 289, 362, 510, 362, 288, 513, 514, 515, 514, 267, 382, 513, 383, 267, 516,
            517, 518, 518, 343, 304, 516, 304, 342, 519, 520, 521, 520, 327, 324, 521, 324, 325, 519, 325, 327, 522,
            523, 524, 524, 267, 383, 522, 383, 266, 525, 526, 527, 527, 290, 360, 525, 360, 289, 528, 529, 530, 530,
            357, 351, 528, 351, 356, 531, 532, 533, 532, 384, 265, 533, 265, 383, 531, 383, 384, 534, 535, 536, 536,
            291, 359, 534, 359, 290, 537, 538, 539, 538, 322, 329, 539, 329, 321, 540, 541, 542, 542, 274, 374, 540,
            374, 273, 543, 544, 545, 545, 359, 292, 543, 292, 358, 546, 547, 548, 548, 324, 328, 546, 328, 323, 549,
            550, 551, 550, 265, 266, 551, 266, 383, 549, 383, 265, 552, 553, 554, 554, 294, 358, 552, 358, 293, 555,
            556, 557, 556, 294, 357, 555, 358, 294, 558, 559, 560, 560, 344, 303, 558, 303, 343, 561, 562, 563, 563,
            356, 351, 561, 351, 355, 564, 565, 566, 564, 354, 352, 567, 568, 569, 569, 315, 336, 567, 336, 314, 570,
            571, 572, 571, 296, 349, 572, 349, 295, 573, 574, 575, 574, 297, 348, 575, 348, 296, 576, 577, 578, 577,
            264, 265, 578, 265, 384, 576, 384, 264, 579, 580, 581, 580, 298, 347, 581, 347, 297, 582, 583, 584, 584,
            355, 352, 582, 352, 354, 585, 586, 587, 587, 280, 368, 585, 368, 279, 588, 589, 590, 590, 351, 295, 588,
            295, 350, 591, 592, 593, 592, 317, 333, 591, 334, 317, 594, 595, 596, 596, 370, 277, 594, 277, 369, 597,
            598, 599, 598, 289, 360, 597, 361, 289, 600, 601, 602, 601, 337, 313, 600, 314, 337, 603, 604, 605, 604,
            301, 345, 605, 345, 300, 606, 607, 608, 607, 310, 339, 606, 340, 310, 609, 610, 611, 611, 293, 358, 609,
            358, 292, 612, 613, 614, 614, 365, 284, 612, 284, 364, 615, 616, 617, 616, 302, 344, 617, 344, 301, 618,
            619, 620, 619, 276, 371, 620, 371, 275, 621, 622, 623, 622, 303, 344, 623, 344, 302, 624, 625, 626, 625,
            307, 341, 624, 342, 307, 627, 628, 629, 628, 304, 343, 629, 343, 303, 630, 631, 632, 632, 348, 297, 630,
            297, 347, 633, 634, 635, 634, 263, 384, 635, 384, 262, 633, 262, 263, 636, 637, 638, 637, 305, 342, 638,
            342, 304, 639, 640, 641, 641, 349, 296, 639, 296, 348, 642, 643, 644, 643, 342, 305, 642, 306, 342, 645,
            646, 647, 647, 307, 342, 645, 342, 306, 648, 649, 650, 650, 346, 299, 648, 299, 345, 651, 652, 653, 652,
            261, 262, 653, 262, 385, 651, 385, 261, 654, 655, 656, 655, 341, 307, 654, 308, 341, 657, 658, 659, 659,
            341, 308, 657, 308, 340, 660, 661, 662, 661, 340, 308, 660, 309, 340, 663, 664, 665, 665, 310, 340, 663,
            340, 309, 666, 667, 668, 667, 355, 351, 668, 351, 352, 666, 352, 355, 669, 670, 671, 671, 311, 339, 669,
            339, 310, 672, 673, 674, 673, 382, 268, 672, 269, 382, 675, 676, 677, 677, 327, 325, 678, 679, 680, 679,
            311, 338, 678, 339, 311, 681, 682, 683, 683, 312, 338, 681, 338, 311, 684, 685, 686, 685, 379, 270, 684,
            271, 379, 687, 688, 689, 688, 260, 261, 689, 261, 385, 687, 385, 260, 690, 691, 692, 691, 324, 327, 690,
            328, 324, 693, 694, 695, 695, 338, 313, 693, 313, 337, 696, 697, 698, 697, 329, 323, 698, 323, 328, 699,
            700, 701, 701, 350, 295, 699, 295, 349, 702, 703, 704, 703, 381, 269, 702, 270, 381, 705, 706, 707, 707,
            337, 314, 705, 314, 336, 708, 709, 710, 709, 260, 385, 710, 385, 386, 708, 386, 260, 711, 712, 713, 712,
            384, 385, 713, 385, 262, 711, 262, 384, 714, 715, 716, 715, 368, 280, 716, 280, 367, 717, 718, 719, 719,
            347, 298, 717, 298, 346, 720, 721, 722, 722, 333, 317, 720, 317, 332, 723, 724, 725, 725, 332, 318, 723,
            318, 331, 726, 727, 728, 727, 290, 359, 726, 360, 290, 729, 730, 731, 731, 316, 335, 729, 335, 315, 732,
            733, 734, 733, 323, 329, 734, 329, 322, 735, 736, 737, 736, 287, 362, 735, 363, 287, 738, 739, 740, 740,
            317, 334, 738, 334, 316, 741, 742, 743, 742, 299, 346, 743, 346, 298, 744, 745, 746, 746, 330, 320, 744,
            320, 329, 747, 748, 749, 748, 321, 329, 749, 329, 320, 750, 751, 752, 751, 318, 332, 752, 332, 317, 753,
            754, 755, 754, 259, 260, 755, 260, 386, 753, 386, 259, 756, 757, 758, 757, 320, 330, 758, 330, 319, 759,
            760, 761, 760, 319, 331, 761, 331, 318, 762, 763, 764, 763, 259, 386, 764, 386, 258, 765, 766, 767, 766,
            263, 264, 767, 264, 384, 765, 384, 263, 267, 504, 505, 267, 505, 268, 268, 673, 674, 268, 674, 269, 269,
            703, 704, 269, 704, 270, 270, 685, 686, 270, 686, 271, 266, 522, 523, 266, 523, 267, 266, 550, 549, 266,
            549, 265, 265, 577, 576, 265, 576, 264, 264, 766, 765, 264, 765, 263, 263, 633, 635, 263, 635, 262, 262,
            652, 651, 262, 651, 261, 261, 688, 687, 261, 687, 260, 260, 754, 753, 260, 753, 259, 258, 764, 763, 258,
            763, 386, 258, 764, 762, 258, 762, 259, 386, 710, 709, 386, 709, 385, 385, 712, 711, 385, 711, 384, 384,
            531, 533, 384, 533, 383, 382, 514, 515, 382, 515, 383, 316, 738, 739, 316, 739, 317, 271, 450, 451, 271,
            451, 272, 272, 423, 424, 272, 424, 273, 273, 540, 541, 273, 541, 274, 317, 752, 750, 317, 750, 318, 318,
            761, 759, 318, 759, 319, 319, 758, 756, 319, 756, 320, 320, 749, 747, 320, 747, 321, 321, 539, 537, 321,
            537, 322, 322, 734, 732, 322, 732, 323, 313, 601, 602, 313, 602, 314, 312, 463, 464, 312, 464, 313, 311,
            681, 682, 311, 682, 312, 310, 669, 670, 310, 670, 311, 309, 663, 664, 309, 664, 310, 308, 661, 662, 308,
            662, 309, 314, 567, 568, 314, 568, 315, 315, 729, 730, 315, 730, 316, 352, 668, 667, 352, 667, 351, 350,
            588, 589, 350, 589, 351, 349, 699, 700, 349, 700, 350, 348, 639, 640, 348, 640, 349, 347, 630, 631, 347,
            631, 348, 346, 717, 718, 346, 718, 347, 345, 648, 649, 345, 649, 346, 344, 447, 448, 344, 448, 345, 343,
            558, 559, 343, 559, 344, 342, 516, 517, 342, 517, 343, 341, 625, 626, 341, 626, 342, 340, 657, 658, 340,
            658, 341, 339, 607, 608, 339, 608, 340, 352, 564, 565, 352, 565, 353, 307, 655, 656, 307, 656, 308, 306,
            645, 646, 306, 646, 307, 305, 643, 644, 305, 644, 306, 304, 638, 636, 304, 636, 305, 303, 629, 627, 303,
            627, 304, 301, 617, 615, 301, 615, 302, 302, 623, 621, 302, 621, 303, 300, 605, 603, 300, 603, 301, 299,
            437, 435, 299, 435, 300, 298, 743, 741, 298, 741, 299, 294, 466, 467, 294, 467, 295, 296, 575, 573, 296,
            573, 297, 297, 581, 579, 297, 579, 298, 295, 572, 570, 295, 570, 296, 289, 525, 526, 289, 526, 290, 288,
            510, 511, 288, 511, 289, 287, 508, 509, 287, 509, 288, 286, 498, 499, 286, 499, 287, 290, 534, 535, 290,
            535, 291, 291, 502, 503, 291, 503, 292, 292, 609, 610, 292, 610, 293, 293, 552, 553, 293, 553, 294, 380,
            474, 475, 380, 475, 381, 381, 489, 490, 381, 490, 382, 285, 493, 494, 285, 494, 286, 284, 479, 477, 284,
            477, 285, 283, 426, 427, 283, 427, 284, 282, 495, 496, 282, 496, 283, 281, 440, 438, 281, 438, 282, 280,
            390, 391, 280, 391, 281, 279, 585, 586, 279, 586, 280, 278, 416, 414, 278, 414, 279, 277, 395, 393, 277,
            393, 278, 276, 389, 387, 276, 387, 277, 275, 620, 618, 275, 618, 276, 274, 397, 398, 274, 398, 275, 353,
            565, 566, 353, 566, 354, 354, 582, 583, 354, 583, 355, 355, 561, 562, 355, 562, 356, 356, 528, 529, 356,
            529, 357, 357, 556, 557, 357, 557, 358, 358, 543, 544, 358, 544, 359, 359, 727, 728, 359, 728, 360, 361,
            481, 482, 361, 482, 362, 360, 598, 599, 360, 599, 361, 362, 736, 737, 362, 737, 363, 363, 486, 487, 363,
            487, 364, 364, 612, 613, 364, 613, 365, 366, 453, 454, 366, 454, 367, 365, 473, 471, 365, 471, 366, 367,
            716, 714, 367, 714, 368, 379, 469, 470, 379, 470, 380, 378, 456, 457, 378, 457, 379, 377, 484, 485, 377,
            485, 378, 376, 433, 434, 376, 434, 377, 323, 546, 547, 323, 547, 324, 368, 420, 421, 368, 421, 369, 369,
            594, 595, 369, 595, 370, 370, 429, 430, 370, 430, 371, 371, 399, 400, 371, 400, 372, 372, 411, 412, 372,
            412, 373, 373, 418, 419, 373, 419, 374, 374, 409, 410, 374, 410, 375, 375, 403, 404, 375, 404, 376, 338,
            679, 680, 338, 680, 339, 337, 693, 694, 337, 694, 338, 336, 705, 706, 336, 706, 337, 335, 442, 443, 335,
            443, 336, 334, 445, 446, 334, 446, 335, 333, 592, 593, 333, 593, 334, 332, 720, 721, 332, 721, 333, 331,
            723, 724, 331, 724, 332, 330, 405, 406, 330, 406, 331, 329, 744, 745, 329, 745, 330, 328, 698, 696, 328,
            696, 329, 326, 675, 676, 326, 676, 327, 325, 677, 675, 325, 675, 326, 325, 521, 520, 325, 520, 324, 327,
            691, 692, 327, 692, 328, 221, 222, 351, 169, 170, 299, 220, 221, 350, 168, 169, 298, 219, 220, 349, 167,
            168, 297, 218, 219, 348, 166, 167, 296, 217, 218, 347, 165, 166, 295, 216, 217, 346, 164, 165, 294, 215,
            216, 345, 163, 164, 293, 129, 130, 259, 214, 215, 344, 162, 163, 292, 213, 214, 343, 161, 162, 291, 212,
            213, 342, 160, 161, 290, 211, 212, 341, 159, 160, 289, 210, 211, 340, 158, 159, 288, 209, 210, 339, 157,
            158, 287, 208, 209, 338, 156, 157, 286, 207, 208, 337, 155, 156, 285, 206, 207, 336, 257, 129, 258, 154,
            155, 284, 205, 206, 335, 256, 257, 386, 153, 154, 283, 204, 205, 334, 255, 256, 385, 152, 153, 282, 203,
            204, 333, 254, 255, 384, 151, 152, 281, 202, 203, 332, 253, 254, 383, 150, 151, 280, 201, 202, 331, 252,
            253, 382, 149, 150, 279, 200, 201, 330, 251, 252, 381, 148, 149, 278, 199, 200, 329, 250, 251, 380, 147,
            148, 277, 198, 199, 328, 249, 250, 379, 146, 147, 276, 197, 198, 327, 248, 249, 378, 145, 146, 275, 196,
            197, 326, 247, 248, 377, 144, 145, 274, 195, 196, 325, 246, 247, 376, 143, 144, 273, 194, 195, 324, 245,
            246, 375, 142, 143, 272, 193, 194, 323, 244, 245, 374, 141, 142, 271, 192, 193, 322, 243, 244, 373, 140,
            141, 270, 191, 192, 321, 242, 243, 372, 139, 140, 269, 190, 191, 320, 241, 242, 371, 138, 139, 268, 189,
            190, 319, 240, 241, 370, 137, 138, 267, 188, 189, 318, 239, 240, 369, 136, 137, 266, 187, 188, 317, 238,
            239, 368, 135, 136, 265, 186, 187, 316, 237, 238, 367, 134, 135, 264, 185, 186, 315, 236, 237, 366, 133,
            134, 263, 184, 185, 314, 235, 236, 365, 132, 133, 262, 183, 184, 313, 234, 235, 364, 131, 132, 261, 182,
            183, 312, 233, 234, 363, 130, 131, 260, 181, 182, 311, 232, 233, 362, 180, 181, 310, 231, 232, 361, 179,
            180, 309, 230, 231, 360, 178, 179, 308, 229, 230, 359, 177, 178, 307, 228, 229, 358, 176, 177, 306, 227,
            228, 357, 175, 176, 305, 226, 227, 356, 174, 175, 304, 225, 226, 355, 173, 174, 303, 224, 225, 354, 172,
            173, 302, 223, 224, 353, 171, 172, 301, 51, 52, 181, 0, 1, 130, 103, 104, 233, 52, 53, 182, 1, 2, 131,
            104,
            105, 234, 53, 54, 183, 2, 3, 132, 105, 106, 235, 54, 55, 184, 3, 4, 133, 106, 107, 236, 55, 56, 185, 4,
            5,
            134, 107, 108, 237, 56, 57, 186, 5, 6, 135, 108, 109, 238, 57, 58, 187, 6, 7, 136, 109, 110, 239, 58,
            59,
            188, 7, 8, 137, 110, 111, 240, 59, 60, 189, 8, 9, 138, 111, 112, 241, 60, 61, 190, 9, 10, 139, 112, 113,
            242, 61, 62, 191, 10, 11, 140, 113, 114, 243, 62, 63, 192, 11, 12, 141, 114, 115, 244, 63, 64, 193, 12,
            13,
            142, 115, 116, 245, 64, 65, 194, 13, 14, 143, 116, 117, 246, 65, 66, 195, 14, 15, 144, 117, 118, 247,
            66,
            67, 196, 15, 16, 145, 118, 119, 248, 67, 68, 197, 16, 17, 146, 119, 120, 249, 68, 69, 198, 17, 18, 147,
            120,
            121, 250, 69, 70, 199, 18, 19, 148, 121, 122, 251, 70, 71, 200, 19, 20, 149, 122, 123, 252, 71, 72, 201,
            20,
            21, 150, 123, 124, 253, 72, 73, 202, 21, 22, 151, 124, 125, 254, 73, 74, 203, 22, 23, 152, 125, 126,
            255,
            74, 75, 204, 23, 24, 153, 126, 127, 256, 75, 76, 205, 24, 25, 154, 127, 128, 257, 76, 77, 206, 25, 26,
            155,
            128, 0, 129, 77, 78, 207, 26, 27, 156, 78, 79, 208, 27, 28, 157, 79, 80, 209, 28, 29, 158, 80, 81, 210,
            29,
            30, 159, 81, 82, 211, 30, 31, 160, 82, 83, 212, 31, 32, 161, 83, 84, 213, 32, 33, 162, 84, 85, 214, 33,
            34,
            163, 85, 86, 215, 34, 35, 164, 86, 87, 216, 35, 36, 165, 87, 88, 217, 36, 37, 166, 88, 89, 218, 37, 38,
            167,
            89, 90, 219, 38, 39, 168, 90, 91, 220, 39, 40, 169, 91, 92, 221, 40, 41, 170, 92, 93, 222, 41, 42, 171,
            93,
            94, 223, 42, 43, 172, 94, 95, 224, 43, 44, 173, 95, 96, 225, 44, 45, 174, 96, 97, 226, 45, 46, 175, 97,
            98,
            227, 46, 47, 176, 98, 99, 228, 47, 48, 177, 99, 100, 229, 48, 49, 178, 100, 101, 230, 49, 50, 179, 101,
            102,
            231, 50, 51, 180, 102, 103, 232, 170, 171, 300, 222, 223, 352, 388, 387, 277, 389, 388, 370, 392, 391,
            281,
            390, 392, 367, 394, 393, 278, 395, 394, 369, 397, 396, 373, 396, 398, 275, 401, 400, 372, 399, 401, 275,
            403, 402, 273, 402, 404, 376, 407, 406, 331, 405, 407, 319, 409, 408, 273, 408, 410, 375, 413, 412, 373,
            411, 413, 275, 415, 414, 279, 416, 415, 368, 418, 417, 274, 417, 419, 374, 422, 421, 369, 420, 422, 278,
            425, 424, 273, 423, 425, 376, 428, 427, 284, 426, 428, 365, 431, 430, 371, 429, 431, 276, 433, 432, 272,
            432, 434, 377, 436, 435, 300, 437, 436, 345, 439, 438, 282, 440, 439, 366, 442, 441, 315, 441, 443, 336,
            445, 444, 316, 444, 446, 335, 449, 448, 345, 447, 449, 301, 452, 451, 272, 450, 452, 378, 455, 454, 367,
            453, 455, 281, 458, 457, 379, 456, 458, 271, 460, 459, 357, 461, 460, 295, 459, 461, 351, 463, 462, 338,
            462, 464, 313, 466, 465, 357, 465, 467, 295, 469, 468, 270, 468, 470, 380, 472, 471, 366, 473, 472, 282,
            476, 475, 381, 474, 476, 270, 478, 477, 285, 479, 478, 364, 481, 480, 289, 480, 482, 362, 484, 483, 272,
            483, 485, 378, 488, 487, 364, 486, 488, 285, 491, 490, 382, 489, 491, 269, 493, 492, 363, 492, 494, 286,
            497, 496, 283, 495, 497, 365, 500, 499, 287, 498, 500, 363, 502, 501, 359, 501, 503, 292, 506, 505, 268,
            504, 506, 382, 508, 507, 362, 507, 509, 288, 512, 511, 289, 510, 512, 362, 514, 513, 267, 513, 515, 383,
            518, 517, 343, 516, 518, 304, 520, 519, 327, 521, 520, 324, 519, 521, 325, 524, 523, 267, 522, 524, 383,
            527, 526, 290, 525, 527, 360, 530, 529, 357, 528, 530, 351, 532, 531, 384, 533, 532, 265, 531, 533, 383,
            536, 535, 291, 534, 536, 359, 538, 537, 322, 539, 538, 329, 542, 541, 274, 540, 542, 374, 545, 544, 359,
            543, 545, 292, 548, 547, 324, 546, 548, 328, 550, 549, 265, 551, 550, 266, 549, 551, 383, 554, 553, 294,
            552, 554, 358, 556, 555, 294, 555, 557, 358, 560, 559, 344, 558, 560, 303, 563, 562, 356, 561, 563, 351,
            564, 566, 354, 569, 568, 315, 567, 569, 336, 571, 570, 296, 572, 571, 349, 574, 573, 297, 575, 574, 348,
            577, 576, 264, 578, 577, 265, 576, 578, 384, 580, 579, 298, 581, 580, 347, 584, 583, 355, 582, 584, 352,
            587, 586, 280, 585, 587, 368, 590, 589, 351, 588, 590, 295, 592, 591, 317, 591, 593, 334, 596, 595, 370,
            594, 596, 277, 598, 597, 289, 597, 599, 361, 601, 600, 337, 600, 602, 314, 604, 603, 301, 605, 604, 345,
            607, 606, 310, 606, 608, 340, 611, 610, 293, 609, 611, 358, 614, 613, 365, 612, 614, 284, 616, 615, 302,
            617, 616, 344, 619, 618, 276, 620, 619, 371, 622, 621, 303, 623, 622, 344, 625, 624, 307, 624, 626, 342,
            628, 627, 304, 629, 628, 343, 632, 631, 348, 630, 632, 297, 634, 633, 263, 635, 634, 384, 633, 635, 262,
            637, 636, 305, 638, 637, 342, 641, 640, 349, 639, 641, 296, 643, 642, 342, 642, 644, 306, 647, 646, 307,
            645, 647, 342, 650, 649, 346, 648, 650, 299, 652, 651, 261, 653, 652, 262, 651, 653, 385, 655, 654, 341,
            654, 656, 308, 659, 658, 341, 657, 659, 308, 661, 660, 340, 660, 662, 309, 665, 664, 310, 663, 665, 340,
            667, 666, 355, 668, 667, 351, 666, 668, 352, 671, 670, 311, 669, 671, 339, 673, 672, 382, 672, 674, 269,
            677, 676, 327, 679, 678, 311, 678, 680, 339, 683, 682, 312, 681, 683, 338, 685, 684, 379, 684, 686, 271,
            688, 687, 260, 689, 688, 261, 687, 689, 385, 691, 690, 324, 690, 692, 328, 695, 694, 338, 693, 695, 313,
            697, 696, 329, 698, 697, 323, 701, 700, 350, 699, 701, 295, 703, 702, 381, 702, 704, 270, 707, 706, 337,
            705, 707, 314, 709, 708, 260, 710, 709, 385, 708, 710, 386, 712, 711, 384, 713, 712, 385, 711, 713, 262,
            715, 714, 368, 716, 715, 280, 719, 718, 347, 717, 719, 298, 722, 721, 333, 720, 722, 317, 725, 724, 332,
            723, 725, 318, 727, 726, 290, 726, 728, 360, 731, 730, 316, 729, 731, 335, 733, 732, 323, 734, 733, 329,
            736, 735, 287, 735, 737, 363, 740, 739, 317, 738, 740, 334, 742, 741, 299, 743, 742, 346, 746, 745, 330,
            744, 746, 320, 748, 747, 321, 749, 748, 329, 751, 750, 318, 752, 751, 332, 754, 753, 259, 755, 754, 260,
            753, 755, 386, 757, 756, 320, 758, 757, 330, 760, 759, 319, 761, 760, 331, 763, 762, 259, 764, 763, 386,
            766, 765, 263, 767, 766, 264, 765, 767, 384,
    };



    //--------------------------- LETTER G--------------------------------------

    float vertices_G[SYMBOL_2D_POINT_COUNT * 3 * 2];
    unsigned int indices_G[SYMBOL_2D_TRIANGLE_COUNT * 3 * 2 + (SYMBOL_2D_POINT_COUNT * 3 * 2)];
    get_symbol_points(vertices_G, SYMBOL_2D_POINT_COUNT * 3 * 2, indices_G,
                      SYMBOL_2D_TRIANGLE_COUNT * 3 * 2 + (SYMBOL_2D_POINT_COUNT * 3 * 2), 0.1f);
    float color_G[SYMBOL_2D_POINT_COUNT * 3 * 2 * 3];
    genColors(color_G, SYMBOL_2D_POINT_COUNT * 3 * 2 * 3);


    /// ARRAYS -----------------------LETTER B-------------------------------------/

    static const float vertices_B[] = {
            -0.29f, 0.345f, -0.04f,
            -0.275f, 0.34f, -0.04f,
            -0.255f, 0.35f, -0.04f,
            -0.225f, 0.36f, -0.04f,
            -0.205f, 0.37f, -0.04f,
            -0.225f, 0.235f, -0.04f,
            -0.25f, 0.11f, -0.04f,
            -0.285f, -0.045f, -0.04f,
            -0.335f, -0.235f, -0.04f,
            -0.37f, -0.33f, -0.04f,
            -0.41f, -0.415f, -0.04f,
            -0.425f, -0.45f, -0.04f,
            -0.405f, -0.455f, -0.04f,
            -0.38f, -0.45f, -0.04f,
            -0.33f, -0.415f, -0.04f,
            -0.295f, -0.36f, -0.04f,
            -0.255f, -0.27f, -0.04f,
            -0.215f, -0.155f, -0.04f,
            -0.18f, -0.025f, -0.04f,
            -0.135f, 0.09f, -0.04f,
            -0.09f, 0.195f, -0.04f,
            -0.03f, 0.275f, -0.04f,
            0.015f, 0.335f, -0.04f,
            0.065f, 0.375f, -0.04f,
            0.12f, 0.39f, -0.04f,
            0.17f, 0.39f, -0.04f,
            0.215f, 0.38f, -0.04f,
            0.255f, 0.36f, -0.04f,
            0.285f, 0.33f, -0.04f,
            0.295f, 0.285f, -0.04f,
            0.285f, 0.235f, -0.04f,
            0.26f, 0.195f, -0.04f,
            0.215f, 0.16f, -0.04f,
            0.14f, 0.125f, -0.04f,
            0.03f, 0.085f, -0.04f,
            -0.03f, 0.06f, -0.04f,
            -0.055f, 0.04f, -0.04f,
            -0.07f, 0.025f, -0.04f,
            -0.065f, 0.01f, -0.04f,
            -0.04f, 0.01f, -0.04f,
            0.015f, 0.015f, -0.04f,
            0.085f, 0.005f, -0.04f,
            0.155f, -0.015f, -0.04f,
            0.205f, -0.065f, -0.04f,
            0.235f, -0.115f, -0.04f,
            0.25f, -0.175f, -0.04f,
            0.24f, -0.245f, -0.04f,
            0.215f, -0.3f, -0.04f,
            0.155f, -0.35f, -0.04f,
            0.095f, -0.38f, -0.04f,
            0.02f, -0.39f, -0.04f,
            -0.04f, -0.39f, -0.04f,
            -0.105f, -0.375f, -0.04f,
            -0.15f, -0.345f, -0.04f,
            -0.18f, -0.315f, -0.04f,
            -0.195f, -0.305f, -0.04f,
            -0.24f, -0.32f, -0.04f,
            -0.275f, -0.345f, -0.04f,
            -0.29f, -0.37f, -0.04f,
            -0.295f, -0.375f, -0.04f,
            -0.245f, -0.42f, -0.04f,
            -0.2f, -0.445f, -0.04f,
            -0.135f, -0.46f, -0.04f,
            -0.085f, -0.465f, -0.04f,
            -0.015f, -0.455f, -0.04f,
            0.07f, -0.435f, -0.04f,
            0.165f, -0.395f, -0.04f,
            0.25f, -0.34f, -0.04f,
            0.31f, -0.28f, -0.04f,
            0.345f, -0.21f, -0.04f,
            0.36f, -0.145f, -0.04f,
            0.355f, -0.085f, -0.04f,
            0.34f, -0.03f, -0.04f,
            0.31f, 0.0f, -0.04f,
            0.265f, 0.04f, -0.04f,
            0.205f, 0.07f, -0.04f,
            0.15f, 0.085f, -0.04f,
            0.215f, 0.115f, -0.04f,
            0.29f, 0.16f, -0.04f,
            0.345f, 0.21f, -0.04f,
            0.385f, 0.265f, -0.04f,
            0.405f, 0.325f, -0.04f,
            0.4f, 0.375f, -0.04f,
            0.375f, 0.42f, -0.04f,
            0.33f, 0.445f, -0.04f,
            0.275f, 0.46f, -0.04f,
            0.2f, 0.46f, -0.04f,
            0.135f, 0.44f, -0.04f,
            0.065f, 0.415f, -0.04f,
            0.0f, 0.37f, -0.04f,
            -0.065f, 0.32f, -0.04f,
            -0.12f, 0.255f, -0.04f,
            -0.105f, 0.365f, -0.04f,
            -0.095f, 0.455f, -0.04f,
            -0.105f, 0.46f, -0.04f,
            -0.275f, 0.37f, -0.04f,
            -0.29f, 0.365f, -0.04f,
            -0.29f, 0.345f, 0.04f,
            -0.275f, 0.34f, 0.04f,
            -0.255f, 0.35f, 0.04f,
            -0.225f, 0.36f, 0.04f,
            -0.205f, 0.37f, 0.04f,
            -0.225f, 0.235f, 0.04f,
            -0.25f, 0.11f, 0.04f,
            -0.285f, -0.045f, 0.04f,
            -0.335f, -0.235f, 0.04f,
            -0.37f, -0.33f, 0.04f,
            -0.41f, -0.415f, 0.04f,
            -0.425f, -0.45f, 0.04f,
            -0.405f, -0.455f, 0.04f,
            -0.38f, -0.45f, 0.04f,
            -0.33f, -0.415f, 0.04f,
            -0.295f, -0.36f, 0.04f,
            -0.255f, -0.27f, 0.04f,
            -0.215f, -0.155f, 0.04f,
            -0.18f, -0.025f, 0.04f,
            -0.135f, 0.09f, 0.04f,
            -0.09f, 0.195f, 0.04f,
            -0.03f, 0.275f, 0.04f,
            0.015f, 0.335f, 0.04f,
            0.065f, 0.375f, 0.04f,
            0.12f, 0.39f, 0.04f,
            0.17f, 0.39f, 0.04f,
            0.215f, 0.38f, 0.04f,
            0.255f, 0.36f, 0.04f,
            0.285f, 0.33f, 0.04f,
            0.295f, 0.285f, 0.04f,
            0.285f, 0.235f, 0.04f,
            0.26f, 0.195f, 0.04f,
            0.215f, 0.16f, 0.04f,
            0.14f, 0.125f, 0.04f,
            0.03f, 0.085f, 0.04f,
            -0.03f, 0.06f, 0.04f,
            -0.055f, 0.04f, 0.04f,
            -0.07f, 0.025f, 0.04f,
            -0.065f, 0.01f, 0.04f,
            -0.04f, 0.01f, 0.04f,
            0.015f, 0.015f, 0.04f,
            0.085f, 0.005f, 0.04f,
            0.155f, -0.015f, 0.04f,
            0.205f, -0.065f, 0.04f,
            0.235f, -0.115f, 0.04f,
            0.25f, -0.175f, 0.04f,
            0.24f, -0.245f, 0.04f,
            0.215f, -0.3f, 0.04f,
            0.155f, -0.35f, 0.04f,
            0.095f, -0.38f, 0.04f,
            0.02f, -0.39f, 0.04f,
            -0.04f, -0.39f, 0.04f,
            -0.105f, -0.375f, 0.04f,
            -0.15f, -0.345f, 0.04f,
            -0.18f, -0.315f, 0.04f,
            -0.195f, -0.305f, 0.04f,
            -0.24f, -0.32f, 0.04f,
            -0.275f, -0.345f, 0.04f,
            -0.29f, -0.37f, 0.04f,
            -0.295f, -0.375f, 0.04f,
            -0.245f, -0.42f, 0.04f,
            -0.2f, -0.445f, 0.04f,
            -0.135f, -0.46f, 0.04f,
            -0.085f, -0.465f, 0.04f,
            -0.015f, -0.455f, 0.04f,
            0.07f, -0.435f, 0.04f,
            0.165f, -0.395f, 0.04f,
            0.25f, -0.34f, 0.04f,
            0.31f, -0.28f, 0.04f,
            0.345f, -0.21f, 0.04f,
            0.36f, -0.145f, 0.04f,
            0.355f, -0.085f, 0.04f,
            0.34f, -0.03f, 0.04f,
            0.31f, 0.0f, 0.04f,
            0.265f, 0.04f, 0.04f,
            0.205f, 0.07f, 0.04f,
            0.15f, 0.085f, 0.04f,
            0.215f, 0.115f, 0.04f,
            0.29f, 0.16f, 0.04f,
            0.345f, 0.21f, 0.04f,
            0.385f, 0.265f, 0.04f,
            0.405f, 0.325f, 0.04f,
            0.4f, 0.375f, 0.04f,
            0.375f, 0.42f, 0.04f,
            0.33f, 0.445f, 0.04f,
            0.275f, 0.46f, 0.04f,
            0.2f, 0.46f, 0.04f,
            0.135f, 0.44f, 0.04f,
            0.065f, 0.415f, 0.04f,
            0.0f, 0.37f, 0.04f,
            -0.065f, 0.32f, 0.04f,
            -0.12f, 0.255f, 0.04f,
            -0.105f, 0.365f, 0.04f,
            -0.095f, 0.455f, 0.04f,
            -0.105f, 0.46f, 0.04f,
            -0.275f, 0.37f, 0.04f,
            -0.29f, 0.365f, 0.04f,
    };

    static float color_B[] = {
            0.019917032f, 0.212616708f, 0.612670898f,
            0.892475874f, 0.550852135f, 0.576453439f,
            0.364889827f, 0.347508816f, 0.681075775f,
            0.090701238f, 0.876065739f, 0.370431966f,
            0.625016086f, 0.689093796f, 0.840390597f,
            0.947178301f, 0.824517267f, 0.502793616f,
            0.737031742f, 0.412925735f, 0.085295307f,
            0.374366041f, 0.946148789f, 0.847667295f,
            0.590068545f, 0.319542496f, 0.589031328f,
            0.637841894f, 0.679705562f, 0.534851489f,
            0.317970427f, 0.173042063f, 0.067555867f,
            0.454854025f, 0.195881704f, 0.557504546f,
            0.514460021f, 0.999704388f, 0.09315608f,
            0.073606849f, 0.853950876f, 0.202797235f,
            0.846513314f, 0.510184754f, 0.007129273f,
            0.031368754f, 0.903842954f, 0.267006606f,
            0.738526553f, 0.822520662f, 0.285249065f,
            0.74315892f, 0.640049118f, 0.748962449f,
            0.759163247f, 0.711704944f, 0.878402521f,
            0.617849842f, 0.990312127f, 0.997997731f,
            0.760272292f, 0.397647935f, 0.638620216f,
            0.894266543f, 0.213945545f, 0.910642147f,
            0.733656275f, 0.297921096f, 0.438186367f,
            0.13034786f, 0.416373208f, 0.513388652f,
            0.609423078f, 0.883709357f, 0.094421875f,
            0.458858468f, 0.481674329f, 0.930518725f,
            0.272945462f, 0.873760139f, 0.463194172f,
            0.396039696f, 0.264727219f, 0.967800201f,
            0.704293296f, 0.934061117f, 0.937910893f,
            0.482397044f, 0.70712729f, 0.067884083f,
            0.491971996f, 0.169809659f, 0.913836897f,
            0.063369483f, 0.082078786f, 0.607167243f,
            0.168580312f, 0.568082402f, 0.67977083f,
            0.005981384f, 0.124192531f, 0.603270796f,
            0.515405773f, 0.700947496f, 0.304016625f,
            0.548993303f, 0.4988284f, 0.64488601f,
            0.551709989f, 0.022691381f, 0.717428585f,
            0.716079176f, 0.657789132f, 0.308033374f,
            0.215301762f, 0.21481051f, 0.299579709f,
            0.462923147f, 0.073107396f, 0.222759583f,
            0.469423246f, 0.012319835f, 0.951474872f,
            0.686938815f, 0.057396075f, 0.440205897f,
            0.999559368f, 0.495835733f, 0.926695903f,
            0.380183423f, 0.372829104f, 0.985498704f,
            0.521032833f, 0.663788426f, 0.473309881f,
            0.483883225f, 0.478359378f, 0.495557388f,
            0.316569292f, 0.488569435f, 0.800786277f,
            0.267715309f, 0.126026768f, 0.981719768f,
            0.9134904f, 0.080412958f, 0.98871072f,
            0.086236207f, 0.010106587f, 0.702475536f,
            0.10009304f, 0.924166479f, 0.234019178f,
            0.600754f, 0.736165188f, 0.549661879f,
            0.760839552f, 0.260267155f, 0.676839617f,
            0.097744043f, 0.376788626f, 0.808592992f,
            0.883622609f, 0.481168586f, 0.082372963f,
            0.14445476f, 0.183303771f, 0.318434608f,
            0.134399138f, 0.243453446f, 0.07712483f,
            0.501517981f, 0.115416974f, 0.772556154f,
            0.254231812f, 0.335326907f, 0.591545037f,
            0.780731775f, 0.11948678f, 0.631933875f,
            0.845878697f, 0.09921903f, 0.873749396f,
            0.099957242f, 0.696555678f, 0.970173849f,
            0.896831814f, 0.151757091f, 0.897224458f,
            0.278787271f, 0.980894894f, 0.102972574f,
            0.385220765f, 0.268892499f, 0.168223325f,
            0.866389561f, 0.460884168f, 0.761158748f,
            0.751454728f, 0.59276797f, 0.379986852f,
            0.320563109f, 0.795297953f, 0.824122808f,
            0.962029436f, 0.161434376f, 0.681886724f,
            0.900179539f, 0.134646951f, 0.529604851f,
            0.771629723f, 0.102177326f, 0.47186562f,
            0.12093849f, 0.889284583f, 0.362201136f,
            0.175365574f, 0.348632298f, 0.726590613f,
            0.789526389f, 0.05819325f, 0.207769274f,
            0.035912995f, 0.294725798f, 0.503324937f,
            0.680545704f, 0.386060962f, 0.808691968f,
            0.502915282f, 0.261151798f, 0.273466809f,
            0.490688935f, 0.805438158f, 0.048668981f,
            0.69485521f, 0.399827939f, 0.89773374f,
            0.31628214f, 0.636439257f, 0.754811926f,
            0.030223076f, 0.624497812f, 0.099997601f,
            0.198824415f, 0.473814592f, 0.38530343f,
            0.954835737f, 0.600047017f, 0.429042445f,
            0.096638521f, 0.199484438f, 0.895198666f,
            0.722354282f, 0.160226967f, 0.873878676f,
            0.828458919f, 0.495907273f, 0.137823917f,
            0.383250619f, 0.949702268f, 0.760640072f,
            0.557487381f, 0.096635589f, 0.074782086f,
            0.580895266f, 0.643263579f, 0.687277872f,
            0.952246276f, 0.367735957f, 0.908385563f,
            0.813673222f, 0.956829872f, 0.086267805f,
            0.796307636f, 0.431376897f, 0.812163373f,
            0.175181489f, 0.860625862f, 0.884575077f,
            0.598447218f, 0.366356803f, 0.327371209f,
            0.055079712f, 0.216943965f, 0.888904031f,
            0.451017675f, 0.445770596f, 0.287590705f,
            0.136495899f, 0.219560738f, 0.329543952f,
            0.891406727f, 0.699310115f, 0.562840456f,
            0.202283872f, 0.965439022f, 0.099436675f,
            0.732794607f, 0.55402714f, 0.905011074f,
            0.908644883f, 0.430615152f, 0.545846116f,
            0.508061194f, 0.408328577f, 0.726906015f,
            0.947409326f, 0.211772195f, 0.162409281f,
            0.014464522f, 0.240136028f, 0.757923966f,
            0.958718257f, 0.124316944f, 0.071761989f,
            0.960786825f, 0.611464242f, 0.382160085f,
            0.063980954f, 0.295198541f, 0.166493636f,
            0.775526681f, 0.49618194f, 0.412106743f,
            0.777359637f, 0.156783305f, 0.836650672f,
            0.355372101f, 0.119853026f, 0.956206729f,
            0.015626869f, 0.171781962f, 0.793724921f,
            0.345972775f, 0.506469446f, 0.197305603f,
            0.442432689f, 0.494707867f, 0.913365202f,
            0.298843931f, 0.081979213f, 0.849467827f,
            0.697239222f, 0.999187339f, 0.354518429f,
            0.187715137f, 0.536403188f, 0.66527007f,
            0.298393062f, 0.558910069f, 0.059625615f,
            0.419572688f, 0.848336747f, 0.240901097f,
            0.098007653f, 0.975750357f, 0.749627267f,
            0.036698803f, 0.186507338f, 0.210621575f,
            0.526304253f, 0.382750236f, 0.27296423f,
            0.216058242f, 0.833208276f, 0.817076767f,
            0.904686882f, 0.900770148f, 0.675367513f,
            0.673972328f, 0.517466187f, 0.989000498f,
            0.293475295f, 0.815757977f, 0.891133382f,
            0.003476951f, 0.582095629f, 0.508183624f,
            0.059152244f, 0.894025127f, 0.799990219f,
            0.466853467f, 0.066075027f, 0.738691425f,
            0.202469132f, 0.989842641f, 0.931445905f,
            0.209162522f, 0.154474392f, 0.640770907f,
            0.172019095f, 0.661973817f, 0.034076979f,
            0.638030533f, 0.703087826f, 0.07618425f,
            0.538997902f, 0.142782773f, 0.416043398f,
            0.463004428f, 0.157313038f, 0.086082705f,
            0.908605449f, 0.962360756f, 0.089300589f,
            0.947821564f, 0.648375501f, 0.542456779f,
            0.120439134f, 0.898454638f, 0.978164337f,
            0.539321649f, 0.547968647f, 0.854687962f,
            0.20174562f, 0.261161501f, 0.53675569f,
            0.116080354f, 0.271281449f, 0.724602187f,
            0.45069821f, 0.947861186f, 0.512144932f,
            0.485847623f, 0.777805184f, 0.22603528f,
            0.671647199f, 0.844877773f, 0.936287114f,
            0.852965849f, 0.458125411f, 0.934614416f,
            0.320059558f, 0.132564285f, 0.025328055f,
            0.046749609f, 0.403194813f, 0.472928409f,
            0.464947946f, 0.884669604f, 0.568710668f,
            0.889673762f, 0.625706207f, 0.53104032f,
            0.811633883f, 0.831358465f, 0.943561515f,
            0.337809012f, 0.005057805f, 0.444027954f,
            0.829258269f, 0.053589717f, 0.32824204f,
            0.771521987f, 0.828286646f, 0.627810643f,
            0.140770243f, 0.803549962f, 0.303730986f,
            0.648300271f, 0.030563437f, 0.838609896f,
            0.931223131f, 0.502027794f, 0.073698942f,
            0.303874521f, 0.132886837f, 0.396879991f,
            0.382960404f, 0.834365157f, 0.608557729f,
            0.990727406f, 0.712893065f, 0.239139711f,
            0.633273974f, 0.652013478f, 0.259713876f,
            0.655012001f, 0.772066239f, 0.797719772f,
            0.048599233f, 0.177207458f, 0.468274395f,
            0.208139707f, 0.951427975f, 0.451357051f,
            0.402527169f, 0.294161941f, 0.646171924f,
            0.654088631f, 0.534801774f, 0.542464607f,
            0.415993981f, 0.295398947f, 0.621483751f,
            0.79408151f, 0.132174234f, 0.213451638f,
            0.323852687f, 0.581468055f, 0.32712223f,
            0.798484159f, 0.482631824f, 0.342017929f,
            0.240883359f, 0.554857781f, 0.853421757f,
            0.352481265f, 0.468668793f, 0.767637765f,
            0.006329069f, 0.815999262f, 0.657439101f,
            0.264700641f, 0.267094802f, 0.073137354f,
            0.127319933f, 0.222757249f, 0.673676571f,
            0.095479438f, 0.544664157f, 0.285445996f,
            0.506418742f, 0.811337365f, 0.908765695f,
            0.438757494f, 0.508655385f, 0.106923709f,
            0.726846227f, 0.796037803f, 0.307964764f,
            0.662999456f, 0.80994915f, 0.356182452f,
            0.589006342f, 0.370267195f, 0.686178248f,
            0.213072478f, 0.209132814f, 0.652658852f,
            0.240463339f, 0.786728731f, 0.829348674f,
            0.363675906f, 0.00292013f, 0.214085651f,
            0.008078787f, 0.457365848f, 0.802647644f,
            0.850418174f, 0.236347196f, 0.910862328f,
            0.568475063f, 0.471402742f, 0.540213642f,
            0.787280724f, 0.149354859f, 0.299514673f,
            0.085988831f, 0.083561352f, 0.356120959f,
            0.210202623f, 0.936186438f, 0.747070345f,
            0.081457133f, 0.431232783f, 0.294565432f,
            0.109463031f, 0.365304597f, 0.866902086f,
            0.579943316f, 0.277610761f, 0.247510302f,
            0.302704149f, 0.523332707f, 0.24294515f,
            0.670786354f, 0.854669014f, 0.935639552f,
            0.002497827f, 0.152696891f, 0.106673891f,
    };

    static const unsigned int indices_B[] = {
            62, 158, 159,
            84, 85, 27,
            82, 83, 28,
            79, 29, 30,
            4, 92, 94,
            19, 5, 6,
            83, 84, 28,
            25, 86, 87,
            26, 85, 86,
            60, 61, 53,
            88, 24, 87,
            24, 88, 23,
            26, 86, 25,
            18, 6, 7,
            27, 85, 26,
            81, 82, 28,
            22, 23, 89,
            92, 4, 91,
            3, 4, 95,
            3, 95, 2,
            22, 89, 90,
            39, 37, 38,
            40, 35, 39,
            53, 62, 52,
            2, 95, 1,
            0, 1, 96,
            21, 22, 90,
            81, 28, 29,
            80, 81, 29,
            21, 90, 91,
            80, 29, 79,
            20, 21, 91,
            10, 12, 13,
            20, 91, 5,
            79, 30, 78,
            20, 5, 19,
            60, 54, 56,
            78, 31, 32,
            1, 95, 96,
            78, 32, 77,
            65, 49, 50,
            77, 33, 76,
            77, 32, 33,
            19, 6, 18,
            60, 56, 57,
            76, 34, 41,
            94, 92, 93,
            74, 43, 73,
            41, 34, 40,
            40, 34, 35,
            52, 63, 51,
            4, 94, 95,
            60, 58, 59,
            75, 42, 74,
            39, 36, 37,
            41, 42, 76,
            72, 73, 43,
            14, 9, 10,
            17, 18, 7,
            71, 72, 44,
            17, 7, 8,
            39, 35, 36,
            70, 71, 44,
            70, 44, 45,
            69, 70, 45,
            16, 17, 8,
            69, 45, 46,
            68, 69, 46,
            16, 8, 9,
            68, 46, 47,
            15, 16, 9,
            67, 68, 47,
            67, 47, 48,
            54, 55, 56,
            53, 54, 60,
            15, 9, 14,
            66, 67, 48,
            44, 72, 43,
            60, 57, 58,
            66, 48, 49,
            91, 4, 5,
            28, 84, 27,
            42, 43, 74,
            78, 30, 31,
            66, 49, 65,
            65, 50, 64,
            23, 88, 89,
            76, 33, 34,
            14, 10, 13,
            87, 24, 25,
            76, 42, 75,
            51, 63, 64,
            61, 62, 53,
            11, 12, 10,
            62, 63, 52,
            64, 50, 51,
            173, 139, 138,
            36, 132, 133,
            9, 107, 10,
            89, 185, 186,
            63, 159, 160,
            36, 134, 37,
            10, 108, 11,
            90, 186, 187,
            64, 160, 161,
            37, 135, 38,
            12, 108, 109,
            90, 188, 91,
            65, 161, 162,
            38, 136, 39,
            13, 109, 110,
            92, 188, 189,
            66, 162, 163,
            39, 137, 40,
            14, 110, 111,
            93, 189, 190,
            67, 163, 164,
            41, 137, 138,
            14, 112, 15,
            94, 190, 191,
            67, 165, 68,
            42, 138, 139,
            15, 113, 16,
            95, 191, 192,
            68, 166, 69,
            43, 139, 140,
            17, 113, 114,
            96, 192, 193,
            69, 167, 70,
            44, 140, 141,
            18, 114, 115,
            96, 97, 0,
            70, 168, 71,
            45, 141, 142,
            19, 115, 116,
            71, 169, 72,
            46, 142, 143,
            20, 116, 117,
            72, 170, 73,
            47, 143, 144,
            21, 117, 118,
            73, 171, 74,
            47, 145, 48,
            22, 118, 119,
            74, 172, 75,
            48, 146, 49,
            22, 120, 23,
            75, 173, 76,
            49, 147, 50,
            23, 121, 24,
            77, 173, 174,
            50, 148, 51,
            24, 122, 25,
            78, 174, 175,
            51, 149, 52,
            25, 123, 26,
            79, 175, 176,
            52, 150, 53,
            26, 124, 27,
            0, 98, 1,
            79, 177, 80,
            53, 151, 54,
            27, 125, 28,
            1, 99, 2,
            80, 178, 81,
            54, 152, 55,
            28, 126, 29,
            2, 100, 3,
            81, 179, 82,
            55, 153, 56,
            30, 126, 127,
            3, 101, 4,
            83, 179, 180,
            56, 154, 57,
            31, 127, 128,
            4, 102, 5,
            84, 180, 181,
            58, 154, 155,
            31, 129, 32,
            5, 103, 6,
            85, 181, 182,
            59, 155, 156,
            32, 130, 33,
            6, 104, 7,
            86, 182, 183,
            60, 156, 157,
            34, 130, 131,
            7, 105, 8,
            87, 183, 184,
            61, 157, 158,
            35, 131, 132,
            8, 106, 9,
            88, 184, 185,
            62, 61, 158,
            109, 108, 107,
            109, 107, 110,
            107, 106, 111,
            111, 110, 107,
            113, 112, 106,
            112, 111, 106,
            115, 114, 104,
            114, 113, 105,
            114, 105, 104,
            105, 113, 106,
            116, 115, 103,
            115, 104, 103,
            117, 116, 102,
            116, 103, 102,
            118, 117, 188,
            188, 117, 102,
            119, 118, 187,
            101, 100, 192,
            100, 99, 192,
            99, 98, 192,
            98, 97, 193,
            192, 98, 193,
            192, 191, 101,
            191, 190, 189,
            101, 191, 189,
            102, 101, 188,
            101, 189, 188,
            188, 187, 118,
            187, 186, 119,
            132, 131, 137,
            131, 130, 173,
            137, 131, 138,
            134, 133, 136,
            133, 132, 136,
            136, 135, 134,
            137, 136, 132,
            138, 131, 173,
            130, 129, 174,
            173, 130, 174,
            186, 185, 120,
            119, 186, 120,
            185, 184, 121,
            184, 183, 122,
            121, 184, 122,
            183, 182, 123,
            182, 181, 124,
            123, 182, 124,
            181, 180, 125,
            180, 179, 125,
            181, 125, 124,
            179, 178, 125,
            178, 177, 126,
            125, 178, 126,
            177, 176, 126,
            176, 175, 127,
            127, 175, 128,
            175, 174, 129,
            173, 172, 139,
            172, 171, 139,
            171, 170, 140,
            170, 169, 140,
            169, 168, 141,
            168, 167, 141,
            167, 166, 142,
            166, 165, 143,
            142, 166, 143,
            165, 164, 144,
            164, 163, 145,
            163, 162, 146,
            162, 161, 147,
            146, 162, 147,
            161, 160, 148,
            160, 159, 149,
            159, 158, 150,
            158, 157, 150,
            159, 150, 149,
            157, 156, 155,
            155, 154, 157,
            154, 153, 157,
            153, 152, 151,
            153, 151, 157,
            151, 150, 157,
            160, 149, 148,
            164, 145, 144,
            145, 163, 146,
            141, 167, 142,
            128, 175, 129,
            171, 140, 139,
            121, 120, 185,
            161, 148, 147,
            122, 183, 123,
            165, 144, 143,
            169, 141, 140,
            127, 126, 176,
            36, 35, 132,
            9, 106, 107,
            89, 88, 185,
            63, 62, 159,
            36, 133, 134,
            10, 107, 108,
            90, 89, 186,
            64, 63, 160,
            37, 134, 135,
            12, 11, 108,
            90, 187, 188,
            65, 64, 161,
            38, 135, 136,
            13, 12, 109,
            92, 91, 188,
            66, 65, 162,
            39, 136, 137,
            14, 13, 110,
            93, 92, 189,
            67, 66, 163,
            41, 40, 137,
            14, 111, 112,
            94, 93, 190,
            67, 164, 165,
            42, 41, 138,
            15, 112, 113,
            95, 94, 191,
            68, 165, 166,
            43, 42, 139,
            17, 16, 113,
            96, 95, 192,
            69, 166, 167,
            44, 43, 140,
            18, 17, 114,
            96, 193, 97,
            70, 167, 168,
            45, 44, 141,
            19, 18, 115,
            71, 168, 169,
            46, 45, 142,
            20, 19, 116,
            72, 169, 170,
            47, 46, 143,
            21, 20, 117,
            73, 170, 171,
            47, 144, 145,
            22, 21, 118,
            74, 171, 172,
            48, 145, 146,
            22, 119, 120,
            75, 172, 173,
            49, 146, 147,
            23, 120, 121,
            77, 76, 173,
            50, 147, 148,
            24, 121, 122,
            78, 77, 174,
            51, 148, 149,
            25, 122, 123,
            79, 78, 175,
            52, 149, 150,
            26, 123, 124,
            0, 97, 98,
            79, 176, 177,
            53, 150, 151,
            27, 124, 125,
            1, 98, 99,
            80, 177, 178,
            54, 151, 152,
            28, 125, 126,
            2, 99, 100,
            81, 178, 179,
            55, 152, 153,
            30, 29, 126,
            3, 100, 101,
            83, 82, 179,
            56, 153, 154,
            31, 30, 127,
            4, 101, 102,
            84, 83, 180,
            58, 57, 154,
            31, 128, 129,
            5, 102, 103,
            85, 84, 181,
            59, 58, 155,
            32, 129, 130,
            6, 103, 104,
            86, 85, 182,
            60, 59, 156,
            34, 33, 130,
            7, 104, 105,
            87, 86, 183,
            61, 60, 157,
            35, 34, 131,
            8, 105, 106,
            88, 87, 184,
    };

    //ARRAYS----------------------------LETTER DELTA-------------------------

    float vertices_delta[] = {
            0.242878, 0.635607, -0.3,
            0.218850, 0.638852, -0.3,
            0.195862, 0.641720, -0.3,
            0.173536, 0.644115, -0.3,
            0.151493, 0.645943, -0.3,
            0.129356, 0.647108, -0.3,
            0.106746, 0.647518, -0.3,
            0.082214, 0.646943, -0.3,
            0.057966, 0.645186, -0.3,
            0.034001, 0.642200, -0.3,
            0.010320, 0.637938, -0.3,
            -0.013078, 0.632353, -0.3,
            -0.036192, 0.625397, -0.3,
            -0.053886, 0.618976, -0.3,
            -0.071107, 0.611468, -0.3,
            -0.087667, 0.602637, -0.3,
            -0.103376, 0.592246, -0.3,
            -0.118044, 0.580059, -0.3,
            -0.131484, 0.565839, -0.3,
            -0.141537, 0.554503, -0.3,
            -0.151211, 0.542646, -0.3,
            -0.160412, 0.530317, -0.3,
            -0.169046, 0.517563, -0.3,
            -0.177019, 0.504430, -0.3,
            -0.184235, 0.490967, -0.3,
            -0.189167, 0.480749, -0.3,
            -0.193626, 0.470484, -0.3,
            -0.197423, 0.460124, -0.3,
            -0.200369, 0.449623, -0.3,
            -0.202276, 0.438933, -0.3,
            -0.202953, 0.428006, -0.3,
            -0.201228, 0.412242, -0.3,
            -0.196525, 0.397187, -0.3,
            -0.189553, 0.382700, -0.3,
            -0.181021, 0.368637, -0.3,
            -0.171638, 0.354859, -0.3,
            -0.162114, 0.341222, -0.3,
            -0.144680, 0.319502, -0.3,
            -0.126442, 0.298492, -0.3,
            -0.107448, 0.278048, -0.3,
            -0.087746, 0.258030, -0.3,
            -0.067381, 0.238296, -0.3,
            -0.046402, 0.218704, -0.3,
            -0.084074, 0.179834, -0.3,
            -0.120329, 0.139735, -0.3,
            -0.154882, 0.098312, -0.3,
            -0.187449, 0.055472, -0.3,
            -0.217748, 0.011119, -0.3,
            -0.245494, -0.034841, -0.3,
            -0.264252, -0.070277, -0.3,
            -0.280977, -0.106752, -0.3,
            -0.295055, -0.144172, -0.3,
            -0.305871, -0.182443, -0.3,
            -0.312812, -0.221471, -0.3,
            -0.315262, -0.261160, -0.3,
            -0.312701, -0.305033, -0.3,
            -0.304989, -0.347818, -0.3,
            -0.292077, -0.388996, -0.3,
            -0.273918, -0.428047, -0.3,
            -0.250465, -0.464452, -0.3,
            -0.221671, -0.497689, -0.3,
            -0.199786, -0.515651, -0.3,
            -0.175349, -0.529075, -0.3,
            -0.148926, -0.538528, -0.3,
            -0.121085, -0.544579, -0.3,
            -0.092394, -0.547793, -0.3,
            -0.063418, -0.548738, -0.3,
            -0.013141, -0.544744, -0.3,
            0.035340, -0.533234, -0.3,
            0.081647, -0.514918, -0.3,
            0.125401, -0.490504, -0.3,
            0.166225, -0.460702, -0.3,
            0.203740, -0.426220, -0.3,
            0.242988, -0.381252, -0.3,
            0.275524, -0.331936, -0.3,
            0.301159, -0.279028, -0.3,
            0.319704, -0.223283, -0.3,
            0.330969, -0.165459, -0.3,
            0.334767, -0.106311, -0.3,
            0.330686, -0.060272, -0.3,
            0.319137, -0.015934, -0.3,
            0.301159, 0.026418, -0.3,
            0.277793, 0.066501, -0.3,
            0.250078, 0.104032, -0.3,
            0.219055, 0.138726, -0.3,
            0.057398, 0.293576, -0.3,
            0.029896, 0.319991, -0.3,
            -0.000962, 0.349478, -0.3,
            -0.031725, 0.378871, -0.3,
            -0.058944, 0.405002, -0.3,
            -0.079167, 0.424705, -0.3,
            -0.088943, 0.434812, -0.3,
            -0.096656, 0.443604, -0.3,
            -0.104132, 0.452963, -0.3,
            -0.110852, 0.462890, -0.3,
            -0.116295, 0.473383, -0.3,
            -0.119943, 0.484444, -0.3,
            -0.121274, 0.496072, -0.3,
            -0.116981, 0.520147, -0.3,
            -0.105077, 0.538361, -0.3,
            -0.087029, 0.551375, -0.3,
            -0.064301, 0.559852, -0.3,
            -0.038359, 0.564453, -0.3,
            -0.010667, 0.565839, -0.3,
            0.041713, 0.564941, -0.3,
            0.087335, 0.562625, -0.3,
            0.127379, 0.559458, -0.3,
            0.163026, 0.556007, -0.3,
            0.195460, 0.552840, -0.3,
            0.225861, 0.550524, -0.3,
            0.251386, 0.621993, -0.3,
            -0.005562, 0.184671, -0.3,
            0.025366, 0.153230, -0.3,
            0.056390, 0.120323, -0.3,
            0.086752, 0.086188, -0.3,
            0.115695, 0.051060, -0.3,
            0.142465, 0.015176, -0.3,
            0.166304, -0.021228, -0.3,
            0.181351, -0.045351, -0.3,
            0.195358, -0.070135, -0.3,
            0.207569, -0.095675, -0.3,
            0.217227, -0.122067, -0.3,
            0.223577, -0.149403, -0.3,
            0.225861, -0.177780, -0.3,
            0.224120, -0.216823, -0.3,
            0.218740, -0.256434, -0.3,
            0.209483, -0.295193, -0.3,
            0.196114, -0.331684, -0.3,
            0.178396, -0.364488, -0.3,
            0.156094, -0.392187, -0.3,
            0.137273, -0.409511, -0.3,
            0.116704, -0.425275, -0.3,
            0.094622, -0.438770, -0.3,
            0.071264, -0.449287, -0.3,
            0.046866, -0.456117, -0.3,
            0.021664, -0.458551, -0.3,
            0.000574, -0.457409, -0.3,
            -0.019995, -0.453950, -0.3,
            -0.039808, -0.448129, -0.3,
            -0.058629, -0.439896, -0.3,
            -0.076220, -0.429206, -0.3,
            -0.092346, -0.416010, -0.3,
            -0.121014, -0.381796, -0.3,
            -0.144152, -0.344226, -0.3,
            -0.161901, -0.303914, -0.3,
            -0.174403, -0.261475, -0.3,
            -0.181801, -0.217524, -0.3,
            -0.184235, -0.172675, -0.3,
            -0.179272, -0.109808, -0.3,
            -0.164383, -0.049778, -0.3,
            -0.139567, 0.008550, -0.3,
            -0.104825, 0.066312, -0.3,
            -0.060157, 0.124640, -0.3,
            0.242878, 0.635607, -0.2,
            0.218850, 0.638852, -0.2,
            0.195862, 0.641720, -0.2,
            0.173536, 0.644115, -0.2,
            0.151493, 0.645943, -0.2,
            0.129356, 0.647108, -0.2,
            0.106746, 0.647518, -0.2,
            0.082214, 0.646943, -0.2,
            0.057966, 0.645186, -0.2,
            0.034001, 0.642200, -0.2,
            0.010320, 0.637938, -0.2,
            -0.013078, 0.632353, -0.2,
            -0.036192, 0.625397, -0.2,
            -0.053886, 0.618976, -0.2,
            -0.071107, 0.611468, -0.2,
            -0.087667, 0.602637, -0.2,
            -0.103376, 0.592246, -0.2,
            -0.118044, 0.580059, -0.2,
            -0.131484, 0.565839, -0.2,
            -0.141537, 0.554503, -0.2,
            -0.151211, 0.542646, -0.2,
            -0.160412, 0.530317, -0.2,
            -0.169046, 0.517563, -0.2,
            -0.177019, 0.504430, -0.2,
            -0.184235, 0.490967, -0.2,
            -0.189167, 0.480749, -0.2,
            -0.193626, 0.470484, -0.2,
            -0.197423, 0.460124, -0.2,
            -0.200369, 0.449623, -0.2,
            -0.202276, 0.438933, -0.2,
            -0.202953, 0.428006, -0.2,
            -0.201228, 0.412242, -0.2,
            -0.196525, 0.397187, -0.2,
            -0.189553, 0.382700, -0.2,
            -0.181021, 0.368637, -0.2,
            -0.171638, 0.354859, -0.2,
            -0.162114, 0.341222, -0.2,
            -0.144680, 0.319502, -0.2,
            -0.126442, 0.298492, -0.2,
            -0.107448, 0.278048, -0.2,
            -0.087746, 0.258030, -0.2,
            -0.067381, 0.238296, -0.2,
            -0.046402, 0.218704, -0.2,
            -0.084074, 0.179834, -0.2,
            -0.120329, 0.139735, -0.2,
            -0.154882, 0.098312, -0.2,
            -0.187449, 0.055472, -0.2,
            -0.217748, 0.011119, -0.2,
            -0.245494, -0.034841, -0.2,
            -0.264252, -0.070277, -0.2,
            -0.280977, -0.106752, -0.2,
            -0.295055, -0.144172, -0.2,
            -0.305871, -0.182443, -0.2,
            -0.312812, -0.221471, -0.2,
            -0.315262, -0.261160, -0.2,
            -0.312701, -0.305033, -0.2,
            -0.304989, -0.347818, -0.2,
            -0.292077, -0.388996, -0.2,
            -0.273918, -0.428047, -0.2,
            -0.250465, -0.464452, -0.2,
            -0.221671, -0.497689, -0.2,
            -0.199786, -0.515651, -0.2,
            -0.175349, -0.529075, -0.2,
            -0.148926, -0.538528, -0.2,
            -0.121085, -0.544579, -0.2,
            -0.092394, -0.547793, -0.2,
            -0.063418, -0.548738, -0.2,
            -0.013141, -0.544744, -0.2,
            0.035340, -0.533234, -0.2,
            0.081647, -0.514918, -0.2,
            0.125401, -0.490504, -0.2,
            0.166225, -0.460702, -0.2,
            0.203740, -0.426220, -0.2,
            0.242988, -0.381252, -0.2,
            0.275524, -0.331936, -0.2,
            0.301159, -0.279028, -0.2,
            0.319704, -0.223283, -0.2,
            0.330969, -0.165459, -0.2,
            0.334767, -0.106311, -0.2,
            0.330686, -0.060272, -0.2,
            0.319137, -0.015934, -0.2,
            0.301159, 0.026418, -0.2,
            0.277793, 0.066501, -0.2,
            0.250078, 0.104032, -0.2,
            0.219055, 0.138726, -0.2,
            0.057398, 0.293576, -0.2,
            0.029896, 0.319991, -0.2,
            -0.000962, 0.349478, -0.2,
            -0.031725, 0.378871, -0.2,
            -0.058944, 0.405002, -0.2,
            -0.079167, 0.424705, -0.2,
            -0.088943, 0.434812, -0.2,
            -0.096656, 0.443604, -0.2,
            -0.104132, 0.452963, -0.2,
            -0.110852, 0.462890, -0.2,
            -0.116295, 0.473383, -0.2,
            -0.119943, 0.484444, -0.2,
            -0.121274, 0.496072, -0.2,
            -0.116981, 0.520147, -0.2,
            -0.105077, 0.538361, -0.2,
            -0.087029, 0.551375, -0.2,
            -0.064301, 0.559852, -0.2,
            -0.038359, 0.564453, -0.2,
            -0.010667, 0.565839, -0.2,
            0.041713, 0.564941, -0.2,
            0.087335, 0.562625, -0.2,
            0.127379, 0.559458, -0.2,
            0.163026, 0.556007, -0.2,
            0.195460, 0.552840, -0.2,
            0.225861, 0.550524, -0.2,
            0.251386, 0.621993, -0.2,
            -0.005562, 0.184671, -0.2,
            0.025366, 0.153230, -0.2,
            0.056390, 0.120323, -0.2,
            0.086752, 0.086188, -0.2,
            0.115695, 0.051060, -0.2,
            0.142465, 0.015176, -0.2,
            0.166304, -0.021228, -0.2,
            0.181351, -0.045351, -0.2,
            0.195358, -0.070135, -0.2,
            0.207569, -0.095675, -0.2,
            0.217227, -0.122067, -0.2,
            0.223577, -0.149403, -0.2,
            0.225861, -0.177780, -0.2,
            0.224120, -0.216823, -0.2,
            0.218740, -0.256434, -0.2,
            0.209483, -0.295193, -0.2,
            0.196114, -0.331684, -0.2,
            0.178396, -0.364488, -0.2,
            0.156094, -0.392187, -0.2,
            0.137273, -0.409511, -0.2,
            0.116704, -0.425275, -0.2,
            0.094622, -0.438770, -0.2,
            0.071264, -0.449287, -0.2,
            0.046866, -0.456117, -0.2,
            0.021664, -0.458551, -0.2,
            0.000574, -0.457409, -0.2,
            -0.019995, -0.453950, -0.2,
            -0.039808, -0.448129, -0.2,
            -0.058629, -0.439896, -0.2,
            -0.076220, -0.429206, -0.2,
            -0.092346, -0.416010, -0.2,
            -0.121014, -0.381796, -0.2,
            -0.144152, -0.344226, -0.2,
            -0.161901, -0.303914, -0.2,
            -0.174403, -0.261475, -0.2,
            -0.181801, -0.217524, -0.2,
            -0.184235, -0.172675, -0.2,
            -0.179272, -0.109808, -0.2,
            -0.164383, -0.049778, -0.2,
            -0.139567, 0.008550, -0.2,
            -0.104825, 0.066312, -0.2,
            -0.060157, 0.124640, -0.2,
    };

    unsigned int indices_delta[] = {  // note that we start from 0!
            7, 6, 5,
            7, 5, 4,
            8, 7, 4,
            8, 4, 3,
            9, 8, 3,
            9, 3, 2,
            10, 9, 2,
            10, 2, 1,
            10, 1, 0,
            11, 10, 0,
            11, 0, 110,
            12, 11, 110,
            13, 12, 110,
            13, 110, 109,
            14, 13, 109,
            15, 14, 109,
            16, 15, 109,
            17, 16, 106,
            106, 16, 109,
            18, 17, 103,
            103, 17, 104,
            104, 17, 105,
            105, 17, 106,
            19, 18, 102,
            102, 18, 103,
            19, 102, 101,
            19, 101, 100,
            107, 106, 109,
            108, 107, 109,
            20, 19, 100,
            20, 100, 99,
            21, 20, 99,
            21, 99, 98,
            22, 21, 98,
            22, 98, 97,
            23, 22, 97,
            24, 23, 97,
            24, 97, 96,
            25, 24, 96,
            25, 96, 95,
            26, 25, 95,
            26, 95, 94,
            27, 26, 94,
            27, 94, 93,
            28, 27, 93,
            28, 93, 92,
            29, 28, 92,
            29, 92, 91,
            30, 29, 91,
            30, 91, 90,
            31, 30, 90,
            31, 90, 89,
            32, 31, 89,
            32, 89, 88,
            33, 32, 88,
            34, 33, 88,
            34, 88, 87,
            35, 34, 87,
            36, 35, 87,
            36, 87, 86,
            37, 36, 86,
            37, 86, 85,
            38, 37, 85,
            39, 38, 85,
            39, 85, 84,
            40, 39, 84,
            41, 40, 84,
            42, 41, 84,
            43, 42, 111,
            111, 42, 84,
            43, 111, 152,
            112, 111, 84,
            44, 43, 152,
            113, 112, 84,
            45, 44, 152,
            113, 84, 83,
            45, 152, 151,
            114, 113, 83,
            114, 83, 82,
            46, 45, 151,
            115, 114, 82,
            115, 82, 81,
            46, 151, 150,
            47, 46, 150,
            116, 115, 81,
            116, 81, 80,
            117, 116, 80,
            48, 47, 150,
            48, 150, 149,
            117, 80, 79,
            118, 117, 79,
            49, 48, 149,
            119, 118, 79,
            49, 149, 148,
            119, 79, 78,
            120, 119, 78,
            50, 49, 148,
            121, 120, 78,
            121, 78, 77,
            51, 50, 148,
            51, 148, 147,
            122, 121, 77,
            52, 51, 147,
            123, 122, 77,
            123, 77, 76,
            52, 147, 146,
            124, 123, 76,
            53, 52, 146,
            125, 124, 76,
            53, 146, 145,
            54, 53, 145,
            125, 76, 75,
            126, 125, 75,
            55, 54, 145,
            55, 145, 144,
            126, 75, 74,
            127, 126, 74,
            55, 144, 143,
            56, 55, 143,
            128, 127, 74,
            128, 74, 73,
            56, 143, 142,
            57, 56, 142,
            129, 128, 73,
            129, 73, 72,
            57, 142, 141,
            58, 57, 141,
            130, 129, 72,
            131, 130, 72,
            58, 141, 140,
            132, 131, 72,
            132, 72, 71,
            59, 58, 140,
            59, 140, 139,
            133, 132, 71,
            59, 139, 138,
            59, 138, 137,
            134, 133, 71,
            59, 137, 136,
            135, 134, 71,
            59, 136, 135,
            59, 135, 71,
            59, 71, 70,
            60, 59, 70,
            60, 70, 69,
            61, 60, 69,
            61, 69, 68,
            62, 61, 68,
            63, 62, 68,
            63, 68, 67,
            64, 63, 67,
            65, 64, 67,
            65, 67, 66,
            160, 158, 159,
            160, 157, 158,
            161, 157, 160,
            161, 156, 157,
            162, 156, 161,
            162, 155, 156,
            163, 155, 162,
            163, 154, 155,
            163, 153, 154,
            164, 153, 163,
            164, 263, 153,
            165, 263, 164,
            166, 263, 165,
            166, 262, 263,
            167, 262, 166,
            168, 262, 167,
            169, 262, 168,
            170, 259, 169,
            259, 262, 169,
            171, 256, 170,
            256, 257, 170,
            257, 258, 170,
            258, 259, 170,
            172, 255, 171,
            255, 256, 171,
            172, 254, 255,
            172, 253, 254,
            260, 262, 259,
            261, 262, 260,
            173, 253, 172,
            173, 252, 253,
            174, 252, 173,
            174, 251, 252,
            175, 251, 174,
            175, 250, 251,
            176, 250, 175,
            177, 250, 176,
            177, 249, 250,
            178, 249, 177,
            178, 248, 249,
            179, 248, 178,
            179, 247, 248,
            180, 247, 179,
            180, 246, 247,
            181, 246, 180,
            181, 245, 246,
            182, 245, 181,
            182, 244, 245,
            183, 244, 182,
            183, 243, 244,
            184, 243, 183,
            184, 242, 243,
            185, 242, 184,
            185, 241, 242,
            186, 241, 185,
            187, 241, 186,
            187, 240, 241,
            188, 240, 187,
            189, 240, 188,
            189, 239, 240,
            190, 239, 189,
            190, 238, 239,
            191, 238, 190,
            192, 238, 191,
            192, 237, 238,
            193, 237, 192,
            194, 237, 193,
            195, 237, 194,
            196, 264, 195,
            264, 237, 195,
            196, 305, 264,
            265, 237, 264,
            197, 305, 196,
            266, 237, 265,
            198, 305, 197,
            266, 236, 237,
            198, 304, 305,
            267, 236, 266,
            267, 235, 236,
            199, 304, 198,
            268, 235, 267,
            268, 234, 235,
            199, 303, 304,
            200, 303, 199,
            269, 234, 268,
            269, 233, 234,
            270, 233, 269,
            201, 303, 200,
            201, 302, 303,
            270, 232, 233,
            271, 232, 270,
            202, 302, 201,
            272, 232, 271,
            202, 301, 302,
            272, 231, 232,
            273, 231, 272,
            203, 301, 202,
            274, 231, 273,
            274, 230, 231,
            204, 301, 203,
            204, 300, 301,
            275, 230, 274,
            205, 300, 204,
            276, 230, 275,
            276, 229, 230,
            205, 299, 300,
            277, 229, 276,
            206, 299, 205,
            278, 229, 277,
            206, 298, 299,
            207, 298, 206,
            278, 228, 229,
            279, 228, 278,
            208, 298, 207,
            208, 297, 298,
            279, 227, 228,
            280, 227, 279,
            208, 296, 297,
            209, 296, 208,
            281, 227, 280,
            281, 226, 227,
            209, 295, 296,
            210, 295, 209,
            282, 226, 281,
            282, 225, 226,
            210, 294, 295,
            211, 294, 210,
            283, 225, 282,
            284, 225, 283,
            211, 293, 294,
            285, 225, 284,
            285, 224, 225,
            212, 293, 211,
            212, 292, 293,
            286, 224, 285,
            212, 291, 292,
            212, 290, 291,
            287, 224, 286,
            212, 289, 290,
            288, 224, 287,
            212, 288, 289,
            212, 224, 288,
            212, 223, 224,
            213, 223, 212,
            213, 222, 223,
            214, 222, 213,
            214, 221, 222,
            215, 221, 214,
            216, 221, 215,
            216, 220, 221,
            217, 220, 216,
            218, 220, 217,
            218, 219, 220,
            112, 264, 111,
            93, 245, 92,
            121, 273, 120,
            129, 281, 128,
            29, 181, 28,
            68, 220, 67,
            104, 256, 103,
            44, 196, 43,
            64, 216, 63,
            78, 230, 77,
            105, 257, 104,
            113, 265, 112,
            73, 225, 72,
            92, 244, 91,
            51, 203, 50,
            65, 217, 64,
            30, 182, 29,
            106, 258, 105,
            45, 197, 44,
            142, 294, 141,
            66, 218, 65,
            19, 171, 18,
            58, 210, 57,
            148, 300, 147,
            67, 219, 66,
            91, 243, 90,
            122, 274, 121,
            84, 236, 83,
            130, 282, 129,
            31, 183, 30,
            103, 255, 102,
            52, 204, 51,
            152, 304, 151,
            131, 283, 130,
            7, 159, 6,
            102, 254, 101,
            114, 266, 113,
            90, 242, 89,
            123, 275, 122,
            6, 158, 5,
            32, 184, 31,
            101, 253, 100,
            141, 293, 140,
            107, 259, 106,
            83, 235, 82,
            132, 284, 131,
            5, 157, 4,
            77, 229, 76,
            46, 198, 45,
            8, 160, 7,
            89, 241, 88,
            108, 260, 107,
            33, 185, 32,
            147, 299, 146,
            109, 261, 108,
            115, 267, 114,
            72, 224, 71,
            124, 276, 123,
            20, 172, 19,
            59, 211, 58,
            4, 156, 3,
            34, 186, 33,
            9, 161, 8,
            53, 205, 52,
            82, 234, 81,
            100, 252, 99,
            140, 292, 139,
            88, 240, 87,
            125, 277, 124,
            21, 173, 20,
            151, 303, 150,
            133, 285, 132,
            3, 155, 2,
            35, 187, 34,
            47, 199, 46,
            10, 162, 9,
            36, 188, 35,
            146, 298, 145,
            99, 251, 98,
            116, 268, 115,
            139, 291, 138,
            54, 206, 53,
            22, 174, 21,
            2, 154, 1,
            138, 290, 137,
            87, 239, 86,
            81, 233, 80,
            134, 286, 133,
            1, 153, 0,
            37, 189, 36,
            76, 228, 75,
            98, 250, 97,
            117, 269, 116,
            11, 163, 10,
            126, 278, 125,
            23, 175, 22,
            48, 200, 47,
            137, 289, 136,
            86, 238, 85,
            55, 207, 54,
            24, 176, 23,
            135, 287, 134,
            0, 263, 110,
            38, 190, 37,
            12, 164, 11,
            150, 302, 149,
            39, 191, 38,
            145, 297, 144,
            97, 249, 96,
            136, 288, 135,
            13, 165, 12,
            25, 177, 24,
            80, 232, 79,
            75, 227, 74,
            118, 270, 117,
            85, 237, 84,
            127, 279, 126,
            71, 223, 70,
            110, 262, 109,
            40, 192, 39,
            96, 248, 95,
            49, 201, 48,
            60, 212, 59,
            14, 166, 13,
            26, 178, 25,
            41, 193, 40,
            144, 296, 143,
            119, 271, 118,
            15, 167, 14,
            56, 208, 55,
            70, 222, 69,
            42, 194, 41,
            95, 247, 94,
            61, 213, 60,
            16, 168, 15,
            128, 280, 127,
            27, 179, 26,
            149, 301, 148,
            43, 195, 42,
            17, 169, 16,
            79, 231, 78,
            69, 221, 68,
            74, 226, 73,
            94, 246, 93,
            120, 272, 119,
            62, 214, 61,
            28, 180, 27,
            143, 295, 142,
            50, 202, 49,
            63, 215, 62,
            18, 170, 17,
            111, 305, 152,
            57, 209, 56,
            93, 246, 245,
            29, 182, 181,
            68, 221, 220,
            104, 257, 256,
            44, 197, 196,
            64, 217, 216,
            78, 231, 230,
            105, 258, 257,
            73, 226, 225,
            92, 245, 244,
            51, 204, 203,
            65, 218, 217,
            30, 183, 182,
            106, 259, 258,
            45, 198, 197,
            66, 219, 218,
            19, 172, 171,
            58, 211, 210,
            67, 220, 219,
            91, 244, 243,
            84, 237, 236,
            31, 184, 183,
            103, 256, 255,
            52, 205, 204,
            7, 160, 159,
            102, 255, 254,
            90, 243, 242,
            6, 159, 158,
            32, 185, 184,
            101, 254, 253,
            107, 260, 259,
            83, 236, 235,
            5, 158, 157,
            77, 230, 229,
            46, 199, 198,
            8, 161, 160,
            89, 242, 241,
            108, 261, 260,
            33, 186, 185,
            109, 262, 261,
            72, 225, 224,
            20, 173, 172,
            59, 212, 211,
            4, 157, 156,
            34, 187, 186,
            9, 162, 161,
            53, 206, 205,
            82, 235, 234,
            100, 253, 252,
            88, 241, 240,
            21, 174, 173,
            3, 156, 155,
            35, 188, 187,
            47, 200, 199,
            10, 163, 162,
            36, 189, 188,
            99, 252, 251,
            54, 207, 206,
            22, 175, 174,
            2, 155, 154,
            87, 240, 239,
            81, 234, 233,
            1, 154, 153,
            37, 190, 189,
            76, 229, 228,
            98, 251, 250,
            11, 164, 163,
            23, 176, 175,
            48, 201, 200,
            86, 239, 238,
            55, 208, 207,
            24, 177, 176,
            0, 153, 263,
            38, 191, 190,
            12, 165, 164,
            39, 192, 191,
            97, 250, 249,
            13, 166, 165,
            25, 178, 177,
            80, 233, 232,
            75, 228, 227,
            85, 238, 237,
            71, 224, 223,
            110, 263, 262,
            40, 193, 192,
            96, 249, 248,
            49, 202, 201,
            60, 213, 212,
            14, 167, 166,
            26, 179, 178,
            41, 194, 193,
            15, 168, 167,
            56, 209, 208,
            70, 223, 222,
            42, 195, 194,
            95, 248, 247,
            61, 214, 213,
            16, 169, 168,
            27, 180, 179,
            43, 196, 195,
            17, 170, 169,
            79, 232, 231,
            69, 222, 221,
            74, 227, 226,
            94, 247, 246,
            62, 215, 214,
            28, 181, 180,
            50, 203, 202,
            63, 216, 215,
            18, 171, 170,
            57, 210, 209,
            112, 265, 264,
            121, 274, 273,
            129, 282, 281,
            113, 266, 265,
            142, 295, 294,
            148, 301, 300,
            122, 275, 274,
            130, 283, 282,
            152, 305, 304,
            131, 284, 283,
            114, 267, 266,
            123, 276, 275,
            141, 294, 293,
            132, 285, 284,
            147, 300, 299,
            115, 268, 267,
            124, 277, 276,
            140, 293, 292,
            125, 278, 277,
            151, 304, 303,
            133, 286, 285,
            146, 299, 298,
            116, 269, 268,
            139, 292, 291,
            138, 291, 290,
            134, 287, 286,
            117, 270, 269,
            126, 279, 278,
            137, 290, 289,
            135, 288, 287,
            150, 303, 302,
            145, 298, 297,
            136, 289, 288,
            118, 271, 270,
            127, 280, 279,
            144, 297, 296,
            119, 272, 271,
            128, 281, 280,
            149, 302, 301,
            120, 273, 272,
            143, 296, 295,
            111, 264, 305,
    };

    static const float colors_delta[] = {
            0.118, 0.972, 0.157,
            0.121, 0.038, 0.628,
            0.216, 0.142, 0.220,
            0.294, 0.743, 0.239,
            0.773, 0.853, 0.211,
            0.611, 0.144, 0.170,
            0.097, 0.623, 0.282,
            0.410, 0.124, 0.509,
            0.116, 0.119, 0.312,
            0.014, 0.090, 0.544,
            0.495, 0.109, 0.167,
            0.924, 0.908, 0.293,
            0.003, 0.818, 0.150,
            0.184, 0.792, 0.091,
            0.842, 0.244, 0.381,
            0.447, 0.991, 0.501,
            0.879, 0.534, 0.615,
            0.963, 0.784, 0.345,
            0.698, 0.124, 0.451,
            0.858, 0.155, 0.965,
            0.249, 0.943, 0.789,
            0.549, 0.508, 0.458,
            0.303, 0.271, 0.544,
            0.546, 0.806, 0.121,
            0.204, 0.469, 0.797,
            0.790, 0.691, 0.101,
            0.913, 0.725, 0.664,
            0.584, 0.769, 0.293,
            0.765, 0.641, 0.446,
            0.200, 0.345, 0.864,
            0.896, 0.342, 0.198,
            0.212, 0.517, 0.036,
            0.480, 0.202, 0.263,
            0.830, 0.154, 0.875,
            0.402, 0.612, 0.067,
            0.447, 0.712, 0.334,
            0.271, 0.587, 0.860,
            0.556, 0.675, 0.302,
            0.253, 0.604, 0.738,
            0.977, 0.925, 0.134,
            0.934, 0.559, 0.049,
            0.411, 0.648, 0.369,
            0.255, 0.929, 0.381,
            0.842, 0.257, 0.973,
            0.596, 0.996, 0.984,
            0.903, 0.913, 0.124,
            0.072, 0.450, 0.313,
            0.499, 0.924, 0.792,
            0.649, 0.495, 0.269,
            0.990, 0.769, 0.919,
            0.238, 0.392, 0.536,
            0.529, 0.213, 0.601,
            0.776, 0.323, 0.285,
            0.217, 0.859, 0.583,
            0.379, 0.812, 0.031,
            0.749, 0.229, 0.209,
            0.165, 0.210, 0.146,
            0.469, 0.372, 0.016,
            0.340, 0.408, 0.860,
            0.925, 0.302, 0.942,
            0.377, 0.799, 0.345,
            0.090, 0.997, 0.375,
            0.080, 0.681, 0.822,
            0.336, 0.738, 0.450,
            0.541, 0.140, 0.037,
            0.235, 0.875, 0.664,
            0.345, 0.176, 0.503,
            0.643, 0.837, 0.787,
            0.277, 0.056, 0.660,
            0.360, 0.513, 0.432,
            0.597, 0.132, 0.873,
            0.129, 0.077, 0.619,
            0.463, 0.675, 0.759,
            0.941, 0.256, 0.456,
            0.811, 0.176, 0.618,
            0.086, 0.897, 0.723,
            0.506, 0.586, 0.178,
            0.578, 0.491, 0.640,
            0.579, 0.072, 0.040,
            0.739, 0.172, 0.600,
            0.052, 0.813, 0.913,
            0.098, 0.861, 0.000,
            0.088, 0.280, 0.959,
            0.042, 0.014, 0.422,
            0.732, 0.799, 0.532,
            0.355, 0.132, 0.409,
            0.674, 0.986, 0.273,
            0.096, 0.943, 0.559,
            0.390, 0.695, 0.132,
            0.689, 0.937, 0.274,
            0.637, 0.579, 0.174,
            0.579, 0.470, 0.833,
            0.361, 0.771, 0.371,
            0.843, 0.933, 0.128,
            0.457, 0.282, 0.001,
            0.269, 0.744, 0.929,
            0.582, 0.445, 0.482,
            0.027, 0.784, 0.202,
            0.307, 0.314, 0.644,
            0.944, 0.570, 0.225,
            0.985, 0.325, 0.831,
            0.167, 0.506, 0.857,
            0.182, 0.543, 0.402,
            0.640, 0.136, 0.774,
            0.921, 0.726, 0.052,
            0.923, 0.489, 0.931,
            0.940, 0.967, 0.859,
            0.737, 0.295, 0.737,
            0.714, 0.397, 0.125,
            0.039, 0.502, 0.202,
            0.689, 0.393, 0.260,
            0.984, 0.082, 0.783,
            0.096, 0.047, 0.605,
            0.624, 0.689, 0.146,
            0.416, 0.445, 0.127,
            0.576, 0.147, 0.140,
            0.234, 0.155, 0.859,
            0.021, 0.854, 0.490,
            0.853, 0.058, 0.172,
            0.111, 0.676, 0.642,
            0.430, 0.792, 0.807,
            0.094, 0.186, 0.718,
            0.036, 0.076, 0.192,
            0.545, 0.716, 0.382,
            0.603, 0.512, 0.518,
            0.151, 0.259, 0.314,
            0.111, 0.771, 0.193,
            0.115, 0.733, 0.584,
            0.363, 0.994, 0.663,
            0.760, 0.142, 0.366,
            0.580, 0.842, 0.409,
            0.607, 0.079, 0.707,
            0.172, 0.545, 0.659,
            0.290, 0.050, 0.489,
            0.879, 0.669, 0.604,
            0.297, 0.860, 0.826,
            0.596, 0.680, 0.893,
            0.275, 0.745, 0.948,
            0.681, 0.548, 0.846,
            0.722, 0.598, 0.664,
            0.961, 0.800, 0.673,
            0.274, 0.179, 0.324,
            0.661, 0.996, 0.015,
            0.677, 0.547, 0.664,
            0.527, 0.565, 0.723,
            0.116, 0.522, 0.403,
            0.451, 0.338, 0.665,
            0.575, 0.814, 0.456,
            0.887, 0.315, 0.327,
            0.108, 0.610, 0.229,
            0.703, 0.761, 0.186,
            0.039, 0.051, 0.937,
            0.775, 0.829, 0.193,
            0.703, 0.965, 0.512,
            0.922, 0.096, 0.369,
            0.960, 0.801, 0.359,
            0.285, 0.208, 0.031,
            0.525, 0.563, 0.277,
            0.887, 0.611, 0.522,
            0.060, 0.984, 0.552,
            0.426, 0.874, 0.767,
            0.312, 0.817, 0.474,
            0.590, 0.718, 0.391,
            0.990, 0.534, 0.670,
            0.388, 0.303, 0.515,
            0.155, 0.047, 0.769,
            0.960, 0.790, 0.904,
            0.242, 0.912, 0.201,
            0.435, 0.080, 0.801,
            0.635, 0.746, 0.991,
            0.254, 0.201, 0.361,
            0.254, 0.922, 0.201,
            0.469, 0.181, 0.245,
            0.893, 0.083, 0.451,
            0.508, 0.636, 0.432,
            0.974, 0.142, 0.818,
            0.291, 0.692, 0.065,
            0.147, 0.268, 0.505,
            0.960, 0.716, 0.925,
            0.561, 0.376, 0.470,
            0.320, 0.984, 0.974,
            0.313, 0.717, 0.277,
            0.820, 0.824, 0.029,
            0.482, 0.569, 0.059,
            0.759, 0.728, 0.859,
            0.546, 0.202, 0.884,
            0.572, 0.525, 0.729,
            0.349, 0.758, 0.501,
            0.447, 0.196, 0.954,
            0.899, 0.877, 0.042,
            0.010, 0.165, 0.443,
            0.357, 0.962, 0.101,
            0.822, 0.498, 0.429,
            0.197, 0.650, 0.096,
            0.395, 0.818, 0.493,
            0.326, 0.702, 0.263,
            0.033, 0.057, 0.820,
            0.866, 0.297, 0.714,
            0.213, 0.630, 0.940,
            0.059, 0.436, 0.484,
            0.724, 0.674, 0.820,
            0.847, 0.477, 0.905,
            0.298, 0.252, 0.396,
            0.292, 0.664, 0.063,
            0.251, 0.504, 0.604,
            0.972, 0.152, 0.636,
            0.908, 0.885, 0.641,
            0.994, 0.430, 0.004,
            0.263, 0.388, 0.424,
            0.511, 0.369, 0.084,
            0.025, 0.374, 0.002,
            0.623, 0.833, 0.616,
            0.682, 0.135, 0.233,
            0.343, 0.445, 0.740,
            0.238, 0.642, 0.527,
            0.153, 0.278, 0.735,
            0.989, 0.767, 0.520,
            0.530, 0.109, 0.981,
            0.110, 0.397, 0.458,
            0.778, 0.117, 0.266,
            0.614, 0.933, 0.419,
            0.868, 0.919, 0.053,
            0.052, 0.357, 0.250,
            0.284, 0.473, 0.333,
            0.498, 0.207, 0.754,
            0.746, 0.070, 0.811,
            0.835, 0.104, 0.139,
            0.390, 0.647, 0.469,
            0.652, 0.731, 0.526,
            0.392, 0.067, 0.950,
            0.586, 0.344, 0.726,
            0.568, 0.051, 0.475,
            0.202, 0.915, 0.263,
            0.433, 0.038, 0.891,
            0.965, 0.807, 0.363,
            0.472, 0.199, 0.185,
            0.808, 0.735, 0.565,
            0.050, 0.050, 0.341,
            0.031, 0.160, 0.927,
            0.312, 0.620, 0.368,
            0.135, 0.035, 0.286,
            0.341, 0.336, 0.150,
            0.470, 0.662, 0.491,
            0.979, 0.954, 0.045,
            0.133, 0.014, 0.698,
            0.234, 0.868, 0.650,
            0.321, 0.345, 0.546,
            0.937, 0.965, 0.716,
            0.700, 0.718, 0.816,
            0.357, 0.442, 0.951,
            0.871, 0.112, 0.438,
            0.243, 0.764, 0.275,
            0.194, 0.410, 0.356,
            0.617, 0.421, 0.235,
            0.712, 0.636, 0.255,
            0.578, 0.463, 0.547,
            0.040, 0.403, 0.010,
            0.938, 0.673, 0.037,
            0.205, 0.638, 0.102,
            0.621, 0.776, 0.074,
            0.028, 0.417, 0.918,
            0.431, 0.168, 0.429,
            0.145, 0.352, 0.176,
            0.549, 0.740, 0.248,
            0.252, 0.328, 0.389,
            0.024, 0.070, 0.983,
            0.677, 0.825, 0.661,
            0.990, 0.042, 0.021,
            0.431, 0.338, 0.213,
            0.171, 0.775, 0.829,
            0.672, 0.690, 0.442,
            0.912, 0.906, 0.994,
            0.020, 0.727, 0.305,
            0.759, 0.343, 0.108,
            0.850, 0.454, 0.132,
            0.775, 0.710, 0.626,
            0.383, 0.818, 0.685,
            0.222, 0.148, 0.966,
            0.574, 0.192, 0.329,
            0.900, 0.598, 0.971,
            0.714, 0.387, 0.214,
            0.894, 0.662, 0.036,
            0.041, 0.138, 0.027,
            0.469, 0.768, 0.863,
            0.725, 0.936, 0.888,
            0.636, 0.667, 0.555,
            0.151, 0.351, 0.530,
            0.839, 0.824, 0.547,
            0.939, 0.719, 0.569,
            0.362, 0.046, 0.501,
            0.813, 0.772, 0.639,
            0.736, 0.825, 0.215,
            0.336, 0.854, 0.317,
            0.177, 0.163, 0.441,
            0.338, 0.996, 0.486,
            0.078, 0.798, 0.876,
            0.391, 0.065, 0.462,
            0.646, 0.471, 0.357,
            0.887, 0.117, 0.861,
            0.708, 0.907, 0.520,
            0.976, 0.334, 0.809,
            0.763, 0.077, 0.915,
            0.600, 0.383, 0.697,
            0.492, 0.651, 0.654,
            0.487, 0.908, 0.414,
            0.056, 0.627, 0.173,

    };

    //ARRAYS--------------------------LETTER GAMMA---------------------------------

    static const float vertices_gamma[] = {
            -0.051164, -0.408419, 0.000000,
            -0.029427, -0.419859, 0.000000,
            0.048367, -0.376386, 0.000000,
            0.050655, -0.036608, 0.000000,
            0.100993, 0.152158, 0.000000,
            0.197091, 0.267705, 0.000000,
            0.272598, 0.302026, 0.000000,
            0.337807, 0.275713, 0.000000,
            0.364120, 0.210503, 0.000000,
            0.390433, 0.210503, 0.000000,
            0.376705, 0.304314, 0.000000,
            0.316071, 0.374100, 0.000000,
            0.255437, 0.386685, 0.000000,
            0.184507, 0.368380, 0.000000,
            0.107857, 0.299738, 0.000000,
            0.043791, 0.160166, 0.000000,
            0.011255, 0.018306, 0.000000,
            -0.004762, 0.019450, 0.000000,
            -0.023707, 0.179615, 0.000000,
            -0.090061, 0.322619, 0.000000,
            -0.157559, 0.375244, 0.000000,
            -0.245650, 0.385541, 0.000000,
            -0.322300, 0.345499, 0.000000,
            -0.370349, 0.237960, 0.000000,
            -0.342892, 0.227664, 0.000000,
            -0.325732, 0.269993, 0.000000,
            -0.287979, 0.298594, 0.000000,
            -0.221625, 0.299738, 0.000000,
            -0.160991, 0.266561, 0.000000,
            -0.099213, 0.171606, 0.000000,
            -0.056884, 0.013730, 0.000000,
            -0.044300, -0.151011, 0.000000,
            -0.051164, -0.408419, 0.075597,
            -0.029427, -0.419859, 0.075597,
            0.048367, -0.376386, 0.075597,
            0.050655, -0.036608, 0.075597,
            0.100993, 0.152158, 0.075597,
            0.197091, 0.267705, 0.075597,
            0.272598, 0.302026, 0.075597,
            0.337807, 0.275713, 0.075597,
            0.364120, 0.210503, 0.075597,
            0.390433, 0.210503, 0.075597,
            0.376705, 0.304314, 0.075597,
            0.316071, 0.374100, 0.075597,
            0.255437, 0.386685, 0.075597,
            0.184507, 0.368380, 0.075597,
            0.107857, 0.299738, 0.075597,
            0.043791, 0.160166, 0.075597,
            0.011255, 0.018306, 0.075597,
            -0.004762, 0.019450, 0.075597,
            -0.023707, 0.179615, 0.075597,
            -0.090061, 0.322619, 0.075597,
            -0.157559, 0.375244, 0.075597,
            -0.245650, 0.385541, 0.075597,
            -0.322300, 0.345499, 0.075597,
            -0.370349, 0.237960, 0.075597,
            -0.342892, 0.227664, 0.075597,
            -0.325732, 0.269993, 0.075597,
            -0.287979, 0.298594, 0.075597,
            -0.221625, 0.299738, 0.075597,
            -0.160991, 0.266561, 0.075597,
            -0.099213, 0.171606, 0.075597,
            -0.056884, 0.013730, 0.075597,
            -0.044300, -0.151011, 0.075597
    };


    static const float colors_gamma[] = {
            0.583f, 0.771f, 0.014f,
            0.609f, 0.115f, 0.436f,
            0.327f, 0.483f, 0.844f,
            0.822f, 0.569f, 0.201f,
            0.435f, 0.602f, 0.223f,
            0.310f, 0.747f, 0.185f,
            0.597f, 0.770f, 0.761f,
            0.559f, 0.436f, 0.730f,
            0.359f, 0.583f, 0.152f,
            0.483f, 0.596f, 0.789f,
            0.559f, 0.861f, 0.639f,
            0.195f, 0.548f, 0.859f,
            0.014f, 0.184f, 0.576f,
            0.771f, 0.328f, 0.970f,
            0.406f, 0.615f, 0.116f,
            0.676f, 0.977f, 0.133f,
            0.971f, 0.572f, 0.833f,
            0.140f, 0.616f, 0.489f,
            0.997f, 0.513f, 0.064f,
            0.945f, 0.719f, 0.592f,
            0.543f, 0.021f, 0.978f,
            0.279f, 0.317f, 0.505f,
            0.167f, 0.620f, 0.077f,
            0.347f, 0.857f, 0.137f,
            0.055f, 0.953f, 0.042f,
            0.714f, 0.505f, 0.345f,
            0.783f, 0.290f, 0.734f,
            0.722f, 0.645f, 0.174f,
            0.302f, 0.455f, 0.848f,
            0.225f, 0.587f, 0.040f,
            0.517f, 0.713f, 0.338f,
            0.053f, 0.959f, 0.120f,
            0.393f, 0.621f, 0.362f,
            0.673f, 0.211f, 0.457f,
            0.820f, 0.883f, 0.371f,
            0.982f, 0.099f, 0.879f,
            0.583f, 0.771f, 0.014f,
            0.609f, 0.115f, 0.436f,
            0.327f, 0.483f, 0.844f,
            0.822f, 0.569f, 0.201f,
            0.435f, 0.602f, 0.223f,
            0.310f, 0.747f, 0.185f,
            0.597f, 0.770f, 0.761f,
            0.559f, 0.436f, 0.730f,
            0.359f, 0.583f, 0.152f,
            0.483f, 0.596f, 0.789f,
            0.559f, 0.861f, 0.639f,
            0.195f, 0.548f, 0.859f,
            0.014f, 0.184f, 0.576f,
            0.771f, 0.328f, 0.970f,
            0.406f, 0.615f, 0.116f,
            0.676f, 0.977f, 0.133f,
            0.971f, 0.572f, 0.833f,
            0.140f, 0.616f, 0.489f,
            0.997f, 0.513f, 0.064f,
            0.945f, 0.719f, 0.592f,
            0.543f, 0.021f, 0.978f,
            0.279f, 0.317f, 0.505f,
            0.167f, 0.620f, 0.077f,
            0.347f, 0.857f, 0.137f,
            0.055f, 0.953f, 0.042f,
            0.714f, 0.505f, 0.345f,
            0.783f, 0.290f, 0.734f,
            0.722f, 0.645f, 0.174f
    };


    unsigned int indices_gamma[] = {
            11, 12, 6,
            25, 22, 23,
            26, 21, 22,
            3, 17, 30,
            13, 5, 6,
            26, 22, 25,
            29, 19, 28,
            26, 27, 21,
            27, 28, 20,
            18, 19, 29,
            21, 27, 20,
            6, 7, 11,
            7, 9, 10,
            14, 5, 13,
            5, 14, 4,
            4, 14, 15,
            8, 9, 7,
            23, 24, 25,
            20, 28, 19,
            11, 7, 10,
            17, 18, 30,
            16, 4, 15,
            16, 3, 4,
            16, 17, 3,
            30, 18, 29,
            31, 3, 30,
            31, 2, 3,
            0, 2, 31,
            0, 1, 2,
            6, 12, 13,
            43, 38, 44,
            57, 55, 54,
            58, 54, 53,
            35, 62, 49,
            45, 38, 37,
            58, 57, 54,
            61, 60, 51,
            58, 53, 59,
            59, 52, 60,
            50, 61, 51,
            53, 52, 59,
            38, 43, 39,
            39, 42, 41,
            46, 45, 37,
            37, 36, 46,
            36, 47, 46,
            40, 39, 41,
            55, 57, 56,
            52, 51, 60,
            43, 42, 39,
            49, 62, 50,
            48, 47, 36,
            48, 36, 35,
            48, 35, 49,
            62, 61, 50,
            63, 62, 35,
            63, 35, 34,
            32, 63, 34,
            32, 34, 33,
            38, 45, 44,
            27, 60, 28,
            14, 47, 15,
            1, 34, 2,
            28, 61, 29,
            15, 48, 16,
            2, 35, 3,
            29, 62, 30,
            16, 49, 17,
            3, 36, 4,
            30, 63, 31,
            17, 50, 18,
            4, 37, 5,
            31, 32, 0,
            18, 51, 19,
            5, 38, 6,
            19, 52, 20,
            6, 39, 7,
            20, 53, 21,
            7, 40, 8,
            21, 54, 22,
            8, 41, 9,
            22, 55, 23,
            9, 42, 10,
            23, 56, 24,
            10, 43, 11,
            24, 57, 25,
            11, 44, 12,
            25, 58, 26,
            12, 45, 13,
            26, 59, 27,
            13, 46, 14,
            0, 33, 1,
            27, 59, 60,
            14, 46, 47,
            1, 33, 34,
            28, 60, 61,
            15, 47, 48,
            2, 34, 35,
            29, 61, 62,
            16, 48, 49,
            3, 35, 36,
            30, 62, 63,
            17, 49, 50,
            4, 36, 37,
            31, 63, 32,
            18, 50, 51,
            5, 37, 38,
            19, 51, 52,
            6, 38, 39,
            20, 52, 53,
            7, 39, 40,
            21, 53, 54,
            8, 40, 41,
            9, 41, 42,
            10, 42, 43,
            24, 56, 57,
            11, 43, 44,
            25, 57, 58,
            12, 44, 45,
            26, 58, 59,
            13, 45, 46,
            0, 32, 33,
            22, 54, 55,
            23, 55, 56,
    };

    // END info Y



//------------------------------------------------------------
    unsigned int VAO[NUMBER_LETTERS];
    glGenVertexArrays(NUMBER_LETTERS, VAO);

    unsigned int VBO[NUMBER_LETTERS];
    glGenBuffers(NUMBER_LETTERS, VBO);

    unsigned int EBO[NUMBER_LETTERS];
    glGenBuffers(NUMBER_LETTERS, EBO);

    unsigned int IBO[NUMBER_LETTERS];
    glGenBuffers(NUMBER_LETTERS, IBO);



//-------------------------------LETTER BETA-----------------------------

    //VERTICES BUFFER
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_beta), vertices_beta, GL_STATIC_DRAW);

    //COLORS BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_beta), color_beta, GL_STATIC_DRAW);

    //INDICES BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_beta), indices_beta, GL_STATIC_DRAW);

    //1ST LAYOUT > POSITION
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glVertexAttribPointer(
            0,            // attribute. No particular reason for 0, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );

    //2ND LAYOUT > COLOR
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, EBO[0]);
    glVertexAttribPointer(
            1,            // attribute. No particular reason for 1, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );

//------------------------------LETTER G------------------------------

    //VERTICES BUFFER
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_G), vertices_G, GL_STATIC_DRAW);

    //COLORS BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_G), color_G, GL_STATIC_DRAW);

    //INDICES BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_G), indices_G, GL_STATIC_DRAW);


    //1ST LAYOUT > POSITION
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glVertexAttribPointer(
            0,            // attribute. No particular reason for 0, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );

    //2ND LAYOUT > COLOR
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, EBO[1]);
    glVertexAttribPointer(
            1,            // attribute. No particular reason for 1, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );


    //-------------------------------LETTER B-----------------------------

    //VERTICES BUFFER
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_B), vertices_B, GL_STATIC_DRAW);

    //COLORS BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_B), color_B, GL_STATIC_DRAW);

    //INDICES BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_B), indices_B, GL_STATIC_DRAW);

    //1ST LAYOUT > POSITION
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glVertexAttribPointer(
            0,            // attribute. No particular reason for 0, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );

    //2ND LAYOUT > COLOR
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, EBO[2]);
    glVertexAttribPointer(
            1,            // attribute. No particular reason for 1, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );




    //-------------------------------LETTER DELTA-----------------------------

    //VERTICES BUFFER
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_delta), vertices_delta, GL_STATIC_DRAW);


    //COLORS BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, EBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors_delta), colors_delta, GL_STATIC_DRAW);


    //INDICES BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_delta), indices_delta, GL_STATIC_DRAW);

    //1ST LAYOUT > POSITION
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glVertexAttribPointer(
            0,            // attribute. No particular reason for 0, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );

    //2ND LAYOUT > COLOR
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, EBO[3]);
    glVertexAttribPointer(
            1,            // attribute. No particular reason for 1, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );


    //-------------------------------LETTER GAMMA-----------------------------

    //VERTICES BUFFER
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_gamma), vertices_gamma, GL_STATIC_DRAW);


    //COLORS BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, EBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors_gamma), colors_gamma, GL_STATIC_DRAW);


    //INDICES BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_gamma), indices_gamma, GL_STATIC_DRAW);

    //1ST LAYOUT > POSITION
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glVertexAttribPointer(
            0,            // attribute. No particular reason for 0, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );

    //2ND LAYOUT > COLOR
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, EBO[4]);
    glVertexAttribPointer(
            1,            // attribute. No particular reason for 1, but
            // must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_FALSE,     // normalized?
            0,            // stride
            (void *) nullptr      // array buffer offset
    );


//---------------------------------SHADER--------------------------------------


//------------------------------------------------------------
// Input vertex data, different for all executions of this shader.
// Output data color, will be interpolated for each fragment.
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 vertexColor;\n"
                                     "out vec3 fragmentColor;\n"
                                     "uniform mat4 MVP;\n"
                                     "void main()\n"
                                     "{\n"
                                     " gl_Position = MVP * vec4(aPos, 1.0);\n"
                                     " fragmentColor = vertexColor;\n"
                                     "}\0";


// declare and define fshader, position in color vector declaration
// are RGBA from [0,1] simply in and out
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "in vec3 fragmentColor;\n"
                                       "out vec4 FragColor;\n"
                                       "uniform vec4 newColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   if(newColor[0] == -1)\n"
                                       "   	{FragColor = vec4(fragmentColor, 1.0f);}\n"
                                       "	else\n"
                                       "   	{FragColor = newColor;}\n"
                                       "}\n\0";


// build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders : puts together the vertex and the fragment shaders
    // into a "shader program object"
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for shader linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete shaders, we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    // Model matrix : an identity matrix (model will be at the origin)

    MODEL[0] = glm::mat4(1.0f);
    MODEL[1] = glm::mat4(1.0f);
    MODEL[2] = glm::mat4(1.0f);
    MODEL[3] = glm::mat4(1.0f);
    MODEL[4] = glm::mat4(1.0f);


//        PROJECTION = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.001f, 100.0f); // In world coordinates
    PROJECTION = glm::perspective(glm::radians(70.0f), 8.0f / 8.0f, 0.001f, 100.0f);
    letterPosition();
    // Remember, matrix multiplication is the other way around
    // render loop
    // -----------

    selected_colors[0] = glm::vec4(0, 0, 0, 1);
    selected_colors[1] = glm::vec4(0, 0, 0, 1);
    selected_colors[2] = glm::vec4(0, 0, 0, 1);
    selected_colors[3] = glm::vec4(0, 0, 0, 1);
    selected_colors[4] = glm::vec4(0, 0, 0, 1);

    float r0 = 1.0f;
    float g0 = 0.0f;
    float b0 = 0.0f;


    int flag_r = 1;
    int flag_g = 1;
    int flag_b = 1;


    while (!glfwWindowShouldClose(window)) {
        //input
        //.....

        float i = glfwGetTime();

        if(i <= 0.6) {
            colorBlack();
            colorCustom(0);
        } else if(i <= 1.2) {
            colorBlack();
            colorCustom(1);
        } else if(i <= 1.8) {
            colorBlack();
            colorCustom(2);
        } else if(i <= 2.4) {
            colorBlack();
            colorCustom(3);
        } else if(i <= 3.0) {
            colorBlack();
            colorCustom(4);
        } else if(i <= 3.6) {
            colorBlack();
        } else if(i <= 4.2) {
            colorCustom(0);
            colorCustom(1);
            colorCustom(2);
            colorCustom(3);
            colorCustom(4);
        } else if(i <= 4.8) {
            colorBlack();
        } else if(i <= 5.4) {
            colorCustom(0);
            colorCustom(1);
            colorCustom(2);
            colorCustom(3);
            colorCustom(4);
        } else {

            if(r0 >= 1.0f) {
                flag_r = 0;
            } else if(r0 <= 0.0f) {
                flag_r = 1;
            }

            if(flag_r == 1) {
                r0 += 0.05;

            } else {
                r0 -= 0.05;
            }

            if(g0 >= 1.0f) {
                flag_g = 0;
            } else if(g0 <= 0.0f) {
                flag_g = 1;
            }

            if(flag_g == 1) {
                g0 += 0.05;

            } else {
                g0 -= 0.05;
            }

            if(b0 >= 1.0f) {
                flag_b = 0;
            } else if(b0 <= 0.0f) {
                flag_b = 1;
            }

            if(flag_b == 1) {
                b0 += 0.05;

            } else {
                b0 -= 0.05;
            }

            if (SELECTED_LETTERID == 0) {
                selected_colors[1] = glm::vec4(0, g0, 0, 1);
                selected_colors[2] = glm::vec4(0, 0, b0, 1);
                selected_colors[3] = glm::vec4(0, g0, b0, 1);
                selected_colors[4] = glm::vec4(r0, g0, 0, 1);
            } else if(SELECTED_LETTERID == 1) {
                selected_colors[0] = glm::vec4(r0, 0, 0, 1);
                selected_colors[2] = glm::vec4(0, 0, b0, 1);
                selected_colors[3] = glm::vec4(0, g0, b0, 1);
                selected_colors[4] = glm::vec4(r0, g0, 0, 1);
            }
            else if(SELECTED_LETTERID == 2) {
                selected_colors[0] = glm::vec4(r0, 0, 0, 1);
                selected_colors[1] = glm::vec4(0, 0, b0, 1);
                selected_colors[3] = glm::vec4(0, g0, b0, 1);
                selected_colors[4] = glm::vec4(r0, g0, 0, 1);
            }
            else if(SELECTED_LETTERID == 3) {
                selected_colors[0] = glm::vec4(r0, 0, 0, 1);
                selected_colors[2] = glm::vec4(0, 0, b0, 1);
                selected_colors[1] = glm::vec4(0, g0, b0, 1);
                selected_colors[4] = glm::vec4(r0, g0, 0, 1);
            }
            else if(SELECTED_LETTERID == 4) {
                selected_colors[0] = glm::vec4(r0, 0, 0, 1);
                selected_colors[2] = glm::vec4(0, 0, b0, 1);
                selected_colors[3] = glm::vec4(0, g0, b0, 1);
                selected_colors[1] = glm::vec4(r0, g0, 0, 1);
            } else {
                    selected_colors[0] = glm::vec4(r0, 0, 0, 1);
                    selected_colors[1] = glm::vec4(0, g0, 0, 1);
                    selected_colors[2] = glm::vec4(0, 0, b0, 1);
                    selected_colors[3] = glm::vec4(0, g0, b0, 1);
                    selected_colors[4] = glm::vec4(r0, g0, 0, 1);
            }

        }

        selectLetter(window);

        // render
        // ------

        // Dark blue background
        glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        MVP[0] = PROJECTION * TRANSLATION[0] * VIEW * MODEL[0];

        MVP[1] = PROJECTION * TRANSLATION[1] * VIEW * MODEL[1];

        MVP[2] = PROJECTION * TRANSLATION[2] * VIEW * MODEL[2];

        MVP[3] = PROJECTION * TRANSLATION[3] * VIEW * MODEL[3];

        MVP[4] = PROJECTION * TRANSLATION[4] * VIEW * MODEL[4];


// Get a handle for our "MVP" uniform
        GLint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "newColor");




        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform


        //------------------------------------------------------------


        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        // also clear the depth buffer now!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindVertexArray(VAO[0]);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0][0]);
        glUniform4f(vertexColorLocation, selected_colors[0][0], selected_colors[0][1], selected_colors[0][2],
                    selected_colors[0][3]);
        glDrawElements(GL_TRIANGLES, sizeof(indices_beta) / sizeof(float), GL_UNSIGNED_INT, nullptr);


        glBindVertexArray(VAO[1]);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[1][0][0]);
        glUniform4f(vertexColorLocation, selected_colors[1][0], selected_colors[1][1], selected_colors[1][2],
                    selected_colors[1][3]);
        glDrawElements(GL_TRIANGLES, sizeof(indices_G) / sizeof(float), GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(VAO[2]);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[2][0][0]);
        glUniform4f(vertexColorLocation, selected_colors[2][0], selected_colors[2][1], selected_colors[2][2],
                    selected_colors[2][3]);
        glDrawElements(GL_TRIANGLES, sizeof(indices_B) / sizeof(float), GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(VAO[3]);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[3][0][0]);
        glUniform4f(vertexColorLocation, selected_colors[3][0], selected_colors[3][1], selected_colors[3][2],
                    selected_colors[3][3]);
        glDrawElements(GL_TRIANGLES, sizeof(indices_delta) / sizeof(float), GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(VAO[4]);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[4][0][0]);
        glUniform4f(vertexColorLocation, selected_colors[4][0], selected_colors[4][1], selected_colors[4][2],
                    selected_colors[4][3]);
        glDrawElements(GL_TRIANGLES, sizeof(indices_gamma) / sizeof(float), GL_UNSIGNED_INT, nullptr);



        /* glfw: swap buffers and poll IO events (keys pressed/released,
         mouse moved etc.)
         --------------------------------------------------------------*/
        //cria janela e processa tudo o que nela se passa
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    for (int r = 0; r < NUMBER_LETTERS; ++r) {
        glDeleteVertexArrays(1, &VAO[r]);
        glDeleteBuffers(1, &VBO[r]);
        glDeleteBuffers(1, &EBO[r]);
        glDeleteBuffers(1, &IBO[r]);
    }

    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}



