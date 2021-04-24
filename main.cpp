//1. make
//2. ./pl4/pl4

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define SYMBOL_2D_POINT_COUNT 215
#define SYMBOL_2D_TRIANGLE_COUNT 213

const unsigned int SIMBOL_WIDTH = 501;
const unsigned int SIMBOL_HEIGHT = 445;

// screen settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//
const int NUMBER_LETTERS = 5;

// camera settings
glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,0.5f);
glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,0.0f); // and looks at the origin
glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);  // Head is up (set to 0,-1,0 to look upside-down)

// FOR LETTER Beyblades
float normalize_x(float x)
{
  	x /= (SIMBOL_WIDTH / 2);
  	x -= 1;
  	return x;
}

float normalize_y(float y)
{
  	y /= (SIMBOL_HEIGHT / 2);
  	y -= 1;
  	return -y;
}

unsigned int get_next_point(unsigned int prev)
{
	unsigned int result;
	switch (prev)
	{
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

void get_symbol_points(float* vertices, int vertices_size, unsigned int* indices, int indices_size, float depth)
{
	float symbol_2D_points[] = {
		//first segment
	  	normalize_x(197),  normalize_y(355), 0.0f, //0
  	  	normalize_x(203),  normalize_y(353), 0.0f, //1
  	  	normalize_x(209),  normalize_y(354), 0.0f,
  	  	normalize_x(213),  normalize_y(356), 0.0f,
  	  	normalize_x(220),  normalize_y(359), 0.0f,
  	  	normalize_x(225),  normalize_y(361), 0.0f, //5
  	  	normalize_x(231),  normalize_y(363), 0.0f, 
  	  	normalize_x(243),  normalize_y(366), 0.0f,
  	  	normalize_x(252),  normalize_y(368), 0.0f,
  	  	normalize_x(263),  normalize_y(370), 0.0f,
  	  	normalize_x(267),  normalize_y(371), 0.0f, //10
  	  	normalize_x(273),  normalize_y(370), 0.0f, 
  	  	normalize_x(279),  normalize_y(367), 0.0f,
  	  	normalize_x(284),  normalize_y(365), 0.0f,
  	  	normalize_x(290),  normalize_y(361), 0.0f,
  	  	normalize_x(296),  normalize_y(356), 0.0f, //15
  	  	normalize_x(302),  normalize_y(351), 0.0f, 
  	  	normalize_x(305),  normalize_y(345), 0.0f,
  	  	normalize_x(312),  normalize_y(358), 0.0f,
  	  	normalize_x(305),  normalize_y(364), 0.0f,
  	  	normalize_x(297),  normalize_y(369), 0.0f, //20
  	  	normalize_x(290),  normalize_y(373), 0.0f, 
  	  	normalize_x(279),  normalize_y(378), 0.0f,
  	  	normalize_x(263),  normalize_y(382), 0.0f,
  	  	normalize_x(252),  normalize_y(384), 0.0f,
  	  	normalize_x(243),  normalize_y(385), 0.0f, //25
  	  	normalize_x(231),  normalize_y(385), 0.0f, 
  	  	normalize_x(219),  normalize_y(383), 0.0f,
  	  	normalize_x(207),  normalize_y(380), 0.0f,
  	  	normalize_x(200),  normalize_y(378), 0.0f,
  	  	normalize_x(194),  normalize_y(375), 0.0f, //30
  	  	normalize_x(187),  normalize_y(372), 0.0f, 
  	  	normalize_x(184),  normalize_y(371), 0.0f,
  	  	normalize_x(182),  normalize_y(369), 0.0f,
  	  	normalize_x(183),  normalize_y(367), 0.0f,
  	  	normalize_x(188),  normalize_y(361), 0.0f, //35
  	  	normalize_x(193),  normalize_y(357), 0.0f,

		//second segment
		normalize_x(310),  normalize_y(340), 0.0f,
		normalize_x(313),  normalize_y(334), 0.0f,
		normalize_x(316),  normalize_y(329), 0.0f,
		normalize_x(319),  normalize_y(323), 0.0f, //40
		normalize_x(323),  normalize_y(315), 0.0f,
		normalize_x(327),  normalize_y(306), 0.0f,
		normalize_x(329),  normalize_y(298), 0.0f,
		normalize_x(333),  normalize_y(288), 0.0f,
		normalize_x(336),  normalize_y(280), 0.0f, //45
		normalize_x(336),  normalize_y(276), 0.0f,
		normalize_x(334),  normalize_y(275), 0.0f,
		normalize_x(331),  normalize_y(276), 0.0f,
		normalize_x(328),  normalize_y(279), 0.0f,
		normalize_x(323),  normalize_y(281), 0.0f, //50
		normalize_x(317),  normalize_y(284), 0.0f,
		normalize_x(310),  normalize_y(287), 0.0f,
		normalize_x(306),  normalize_y(290), 0.0f,
		normalize_x(301),  normalize_y(293), 0.0f,
		normalize_x(296),  normalize_y(295), 0.0f, //55
		normalize_x(289),  normalize_y(299), 0.0f,
		normalize_x(283),  normalize_y(301), 0.0f,
		normalize_x(277),  normalize_y(303), 0.0f,
		normalize_x(268),  normalize_y(306), 0.0f,
		normalize_x(259),  normalize_y(308), 0.0f, //60
		normalize_x(251),  normalize_y(309), 0.0f,
		normalize_x(244),  normalize_y(310), 0.0f,
		normalize_x(234),  normalize_y(309), 0.0f,
		normalize_x(227),  normalize_y(307), 0.0f,
		normalize_x(220),  normalize_y(305), 0.0f, //65
		normalize_x(213),  normalize_y(303), 0.0f,
		normalize_x(208),  normalize_y(300), 0.0f,
		normalize_x(203),  normalize_y(296), 0.0f,
		normalize_x(199),  normalize_y(293), 0.0f,
		normalize_x(196),  normalize_y(290), 0.0f, //70
		normalize_x(193),  normalize_y(286), 0.0f,
		normalize_x(189),  normalize_y(282), 0.0f,
		normalize_x(187),  normalize_y(278), 0.0f,
		normalize_x(184),  normalize_y(274), 0.0f,
		normalize_x(215),  normalize_y(263), 0.0f, //75
		normalize_x(218),  normalize_y(268), 0.0f,
		normalize_x(222),  normalize_y(271), 0.0f,
		normalize_x(226),  normalize_y(274), 0.0f,
		normalize_x(230),  normalize_y(278), 0.0f,
		normalize_x(238),  normalize_y(283), 0.0f, //80
		normalize_x(246),  normalize_y(287), 0.0f,
		normalize_x(260),  normalize_y(290), 0.0f,
		normalize_x(268),  normalize_y(291), 0.0f,
		normalize_x(273),  normalize_y(291), 0.0f,
		normalize_x(281),  normalize_y(290), 0.0f, //85
		normalize_x(289),  normalize_y(289), 0.0f,
		normalize_x(294),  normalize_y(288), 0.0f,
		normalize_x(300),  normalize_y(285), 0.0f,
		normalize_x(306),  normalize_y(282), 0.0f,
		normalize_x(311),  normalize_y(278), 0.0f, //90
		normalize_x(316),  normalize_y(275), 0.0f,
		normalize_x(321),  normalize_y(272), 0.0f,
		normalize_x(325),  normalize_y(269), 0.0f,
		normalize_x(327),  normalize_y(265), 0.0f,
		normalize_x(331),  normalize_y(261), 0.0f, //95
		normalize_x(334),  normalize_y(257), 0.0f,
		normalize_x(337),  normalize_y(253), 0.0f,
		normalize_x(341),  normalize_y(247), 0.0f,
		normalize_x(344),  normalize_y(241), 0.0f,
		normalize_x(348),  normalize_y(231), 0.0f, //100
		normalize_x(352),  normalize_y(223), 0.0f,
		normalize_x(354),  normalize_y(216), 0.0f,
		normalize_x(357),  normalize_y(211), 0.0f,
		normalize_x(360),  normalize_y(205), 0.0f,
		normalize_x(363),  normalize_y(202), 0.0f, //105
		normalize_x(370),  normalize_y(199), 0.0f,
		normalize_x(375),  normalize_y(195), 0.0f,
		normalize_x(380),  normalize_y(196), 0.0f,
		normalize_x(381),  normalize_y(199), 0.0f,
		normalize_x(380),  normalize_y(206), 0.0f, //110
		normalize_x(379),  normalize_y(214), 0.0f,
		normalize_x(377),  normalize_y(225), 0.0f,
		normalize_x(373),  normalize_y(239), 0.0f,
		normalize_x(370),  normalize_y(247), 0.0f,
		normalize_x(366),  normalize_y(261), 0.0f, //115
		normalize_x(363),  normalize_y(270), 0.0f,
		normalize_x(359),  normalize_y(281), 0.0f,
		normalize_x(356),  normalize_y(289), 0.0f,
		normalize_x(352),  normalize_y(300), 0.0f,
		normalize_x(348),  normalize_y(309), 0.0f, //120
		normalize_x(344),  normalize_y(314), 0.0f,
		normalize_x(339),  normalize_y(324), 0.0f,
		normalize_x(335),  normalize_y(329), 0.0f,
		normalize_x(328),  normalize_y(339), 0.0f,
		normalize_x(323),  normalize_y(348), 0.0f, //125
		normalize_x(317),  normalize_y(354), 0.0f,

		//third segment
		normalize_x(180),  normalize_y(266), 0.0f,
		normalize_x(177),  normalize_y(255), 0.0f,
		normalize_x(175),  normalize_y(242), 0.0f,
		normalize_x(174),  normalize_y(231), 0.0f, //130
		normalize_x(174),  normalize_y(222), 0.0f,
		normalize_x(175),  normalize_y(213), 0.0f,
		normalize_x(176),  normalize_y(201), 0.0f,
		normalize_x(178),  normalize_y(191), 0.0f,
		normalize_x(181),  normalize_y(181), 0.0f, //135
		normalize_x(184),  normalize_y(171), 0.0f,
		normalize_x(187),  normalize_y(163), 0.0f,
		normalize_x(191),  normalize_y(155), 0.0f,
		normalize_x(197),  normalize_y(145), 0.0f,
		normalize_x(204),  normalize_y(133), 0.0f, //140
		normalize_x(210),  normalize_y(126), 0.0f,
		normalize_x(218),  normalize_y(116), 0.0f,
		normalize_x(226),  normalize_y(108), 0.0f,
		normalize_x(233),  normalize_y(101), 0.0f,
		normalize_x(239),  normalize_y(97), 0.0f, //145
		normalize_x(245),  normalize_y(92), 0.0f,
		normalize_x(252),  normalize_y(86), 0.0f,
		normalize_x(262),  normalize_y(80), 0.0f,
		normalize_x(274),  normalize_y(74), 0.0f,
		normalize_x(278),  normalize_y(72), 0.0f, //150
		normalize_x(286),  normalize_y(68), 0.0f,
		normalize_x(294),  normalize_y(65), 0.0f,
		normalize_x(299),  normalize_y(64), 0.0f,
		normalize_x(305),  normalize_y(62), 0.0f,
		normalize_x(310),  normalize_y(60), 0.0f, //155
		normalize_x(317),  normalize_y(59), 0.0f,
		normalize_x(326),  normalize_y(58), 0.0f,
		normalize_x(332),  normalize_y(57), 0.0f,
		normalize_x(345),  normalize_y(57), 0.0f,
		normalize_x(370),  normalize_y(58), 0.0f, //160
		normalize_x(379),  normalize_y(60), 0.0f,
		normalize_x(385),  normalize_y(63), 0.0f,
		normalize_x(391),  normalize_y(67), 0.0f,
		normalize_x(394),  normalize_y(72), 0.0f,
		normalize_x(395),  normalize_y(78), 0.0f, //165
		normalize_x(395),  normalize_y(84), 0.0f,
		normalize_x(394),  normalize_y(90), 0.0f,
		normalize_x(392),  normalize_y(96), 0.0f,
		normalize_x(390),  normalize_y(101), 0.0f,
		normalize_x(387),  normalize_y(108), 0.0f, //170
		normalize_x(380),  normalize_y(118), 0.0f,
		normalize_x(374),  normalize_y(125), 0.0f,
		normalize_x(365),  normalize_y(133), 0.0f,
		normalize_x(359),  normalize_y(138), 0.0f,
		normalize_x(353),  normalize_y(140), 0.0f, //175
		normalize_x(350),  normalize_y(140), 0.0f,
		normalize_x(351),  normalize_y(137), 0.0f,
		normalize_x(356),  normalize_y(131), 0.0f,
		normalize_x(360),  normalize_y(124), 0.0f,
		normalize_x(362),  normalize_y(119), 0.0f, //180
		normalize_x(368),  normalize_y(105), 0.0f,
		normalize_x(370),  normalize_y(99), 0.0f,
		normalize_x(370),  normalize_y(95), 0.0f,
		normalize_x(369),  normalize_y(91), 0.0f,
		normalize_x(366),  normalize_y(86), 0.0f, //185
		normalize_x(363),  normalize_y(81), 0.0f,
		normalize_x(356),  normalize_y(76), 0.0f,
		normalize_x(349),  normalize_y(74), 0.0f,
		normalize_x(342),  normalize_y(72), 0.0f,
		normalize_x(325),  normalize_y(71), 0.0f, //190
		normalize_x(304),  normalize_y(72), 0.0f,
		normalize_x(290),  normalize_y(73), 0.0f,
		normalize_x(283),  normalize_y(76), 0.0f,
		normalize_x(273),  normalize_y(80), 0.0f,
		normalize_x(268),  normalize_y(83), 0.0f, //195
		normalize_x(261),  normalize_y(87), 0.0f,
		normalize_x(256),  normalize_y(91), 0.0f,
		normalize_x(252),  normalize_y(94), 0.0f,
		normalize_x(248),  normalize_y(97), 0.0f,
		normalize_x(241),  normalize_y(104), 0.0f, //200
		normalize_x(235),  normalize_y(112), 0.0f,
		normalize_x(229),  normalize_y(120), 0.0f,
		normalize_x(222),  normalize_y(133), 0.0f,
		normalize_x(215),  normalize_y(147), 0.0f,
		normalize_x(211),  normalize_y(158), 0.0f, //205
		normalize_x(208),  normalize_y(168), 0.0f,
		normalize_x(206),  normalize_y(180), 0.0f,
		normalize_x(205),  normalize_y(189), 0.0f,
		normalize_x(204),  normalize_y(201), 0.0f,
		normalize_x(203),  normalize_y(211), 0.0f, //210
		normalize_x(203),  normalize_y(226), 0.0f,
		normalize_x(204),  normalize_y(235), 0.0f,
		normalize_x(206),  normalize_y(243), 0.0f,
		normalize_x(209),  normalize_y(251), 0.0f
		
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
	if (depth > 0.0f)
	{
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
	for (int i = 0; i < vertices_front_size; i++)
	{
		if (i % 3 != 2)
		{
			vertices[i] = symbol_2D_points[i];
			//printf("%f, ", vertices[i]);
		}
		else
		{
			vertices[i] = symbol_2D_points[i] + depth / 2;
			//printf("%f\nvertice: ", vertices[i]);
		}
	}

	//printf("Back vertice: ");
	for (int i = 0; i < vertices_back_size; i++)
	{
		if (i % 3 != 2)
		{
			vertices[i + vertices_front_size] = symbol_2D_points[i];
			//printf("%f, ", vertices[i + vertices_front_size]);
		}
		else
		{
			vertices[i + vertices_front_size] = symbol_2D_points[i] - depth / 2;
			//printf("%f\nBack vertice: ", vertices[i + vertices_front_size]);
		}
	}

	//printf("indice: ");
	for (int i = 0; i < indices_front_size; i++)
	{
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

	for (int i = 0; i < indices_back_size; i+=3)
	{
		indices[i + indices_front_size] = symbol_2D_indices[i + 2] + vertices_front_size / 3;
		indices[i + indices_front_size + 1] = symbol_2D_indices[i + 1] + vertices_front_size / 3;
		indices[i + indices_front_size + 2] = symbol_2D_indices[i] + vertices_front_size / 3;

		//printf("Back indice: %u, %u, %u\n", indices[i + indices_front_size], indices[i + indices_front_size + 1], indices[i + indices_front_size + 2]);
	}

	unsigned int current_point = 0;
	for (int i = 0; i < indices_side_size; i+=6)
	{
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


//============================================
/* process all input: query GLFW whether relevant keys are pressed/released 
this frame and react accordingly 
-----------------------------------------------------------------------*/
// Funcao que deteta o Enter
void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
	cameraPos = glm::vec3(-1.0f,0.0f,0.0f);
  }
  else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
  	cameraPos = glm::vec3(1.0f,0.0f,0.0f);
  }
  else if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
    cameraPos = glm::vec3(0.0f,100.0f,1.0f);
  }
  else if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
    cameraPos = glm::vec3(0.0f,-50.0f,1.0f);
  }
  else if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
    cameraPos = glm::vec3(0.0f,0.0f,1.0f);
  }
  else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    cameraPos = glm::vec3(0.0f,0.0f,-1.0f);

  }
}

/* glfw: whenever the window size changed (by OS or user resize) this
   callback function executes
   -------------------------------------------------------------------*/
// Funcao que cria a janela e deteta movimento, dimensoes,etc
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that
  // width and height will be significantly larger than specified on
  // retina displays.
  glViewport(0, 0, width, height);
}



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
    "in vec3 fragmentColor;\n;"
    "out vec3 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = fragmentColor;\n"
    "}\n\0";





int main()
{

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw window creation
  // --------------------
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Letra 3D", NULL,
                                        NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }


//------------------------------------------------------------
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // set up vertex data with depth
// ----------------------------------------
  // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive
    // vertices give a triangle. A cube has 6 faces with 2 triangles each, so this
    // makes 6*2=12 triangles, and 12*3 vertices
    // ------------------------------------------------------------------
    

	// One color for each vertex. They were generated randomly.
static const float color_beta[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f,
        0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
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

unsigned int indices_beta[]={
    19,18,112,22,109,23,20,19,111,115,17,16,113,17,114,15,118,117,72,61,73,15,117,116,114,17,115,21,20,110,16,116,115,110,20,111,14,118,15,25,107,26,112,18,113,14,119,118,42,41,87,24,23,108,57,78,77,58,77,76,86,43,87,13,120,14,108,23,109,120,13,121,99,93,37,80,55,54,99,37,36,12,122,121,108,107,24,122,12,123,27,26,106,31,104,103,14,120,119,105,27,106,123,11,124,105,28,27,24,107,25,28,105,29,101,34,33,9,124,10,104,30,29,30,104,31,9,125,124,84,46,85,69,67,66,8,125,9,31,102,32,98,93,99,126,125,7,32,101,33,64,63,71,15,116,16,100,34,101,65,70,66,7,125,8,35,100,36,36,100,99,221,351,350,85,45,86,97,93,98,94,96,95,56,78,57,38,37,91,39,38,90,6,126,7,40,39,89,96,94,97,21,110,22,92,37,93,59,76,75,111,19,112,31,103,102,79,56,55,43,42,87,52,82,81,34,100,35,106,26,107,44,43,86,18,17,113,45,44,86,49,84,83,46,45,85,89,39,90,5,4,126,47,46,84,90,38,91,84,48,47,48,84,49,87,41,88,3,127,4,83,50,49,82,50,83,82,51,50,51,82,52,97,94,93,52,81,53,124,11,10,68,67,69,53,81,80,53,80,54,121,13,12,2,127,3,66,70,69,79,55,80,71,70,65,91,37,92,123,12,11,78,56,79,2,128,127,126,4,127,110,109,22,88,40,89,74,59,75,73,60,74,32,102,101,57,77,58,65,64,71,29,105,104,58,76,59,41,40,88,71,62,72,63,62,71,60,59,74,1,128,2,62,61,72,61,60,73,1,0,128,5,126,6,169,299,298,220,350,349,168,298,297,219,349,348,167,297,296,218,348,347,166,296,295,217,347,346,165,295,294,216,346,345,164,294,293,215,345,344,163,293,292,129,259,258,214,344,343,162,292,291,213,343,342,161,291,290,212,342,341,160,290,289,211,341,340,159,289,288,210,340,339,158,288,287,209,339,338,157,287,286,208,338,337,156,286,285,207,337,336,155,285,284,206,336,335,257,258,386,154,284,283,205,335,334,256,386,385,153,283,282,204,334,333,255,385,384,152,282,281,203,333,332,254,384,383,151,281,280,202,332,331,253,383,382,150,280,279,201,331,330,252,382,381,149,279,278,200,330,329,251,381,380,148,278,277,199,329,328,250,380,379,147,277,276,198,328,327,249,379,378,146,276,275,197,327,326,248,378,377,145,275,274,196,326,325,247,377,376,144,274,273,195,325,324,246,376,375,143,273,272,194,324,323,245,375,374,142,272,271,193,323,322,244,374,373,141,271,270,192,322,321,243,373,372,140,270,269,191,321,320,242,372,371,139,269,268,190,320,319,241,371,370,138,268,267,189,319,318,240,370,369,137,267,266,188,318,317,239,369,368,136,266,265,187,317,316,238,368,367,135,265,264,186,316,315,237,367,366,134,264,263,185,315,314,236,366,365,133,263,262,184,314,313,235,365,364,132,262,261,183,313,312,234,364,363,131,261,260,182,312,311,233,363,362,130,260,259,181,311,310,232,362,361,180,310,309,231,361,360,179,309,308,230,360,359,178,308,307,229,359,358,177,307,306,228,358,357,176,306,305,227,357,356,175,305,304,226,356,355,174,304,303,225,355,354,173,303,302,224,354,353,172,302,301,223,353,352,171,301,300,51,181,180,0,130,129,103,233,232,52,182,181,1,131,130,104,234,233,53,183,182,2,132,131,105,235,234,54,184,183,3,133,132,106,236,235,55,185,184,4,134,133,107,237,236,56,186,185,5,135,134,108,238,237,57,187,186,6,136,135,109,239,238,58,188,187,7,137,136,110,240,239,59,189,188,8,138,137,111,241,240,60,190,189,9,139,138,112,242,241,61,191,190,10,140,139,113,243,242,62,192,191,11,141,140,114,244,243,63,193,192,12,142,141,115,245,244,64,194,193,13,143,142,116,246,245,65,195,194,14,144,143,117,247,246,66,196,195,15,145,144,118,248,247,67,197,196,16,146,145,119,249,248,68,198,197,17,147,146,120,250,249,69,199,198,18,148,147,121,251,250,70,200,199,19,149,148,122,252,251,71,201,200,20,150,149,123,253,252,72,202,201,21,151,150,124,254,253,73,203,202,22,152,151,125,255,254,74,204,203,23,153,152,126,256,255,75,205,204,24,154,153,127,257,256,76,206,205,25,155,154,128,129,257,77,207,206,26,156,155,78,208,207,27,157,156,79,209,208,28,158,157,80,210,209,29,159,158,81,211,210,30,160,159,82,212,211,31,161,160,83,213,212,32,162,161,84,214,213,33,163,162,85,215,214,34,164,163,86,216,215,35,165,164,87,217,216,36,166,165,88,218,217,37,167,166,89,219,218,38,168,167,90,220,219,39,169,168,91,221,220,40,170,169,92,222,221,41,171,170,93,223,222,42,172,171,94,224,223,43,173,172,95,225,224,44,174,173,96,226,225,45,175,174,97,227,226,46,176,175,98,228,227,47,177,176,99,229,228,48,178,177,100,230,229,49,179,178,101,231,230,50,180,179,102,232,231,170,300,299,222,352,351,387,388,389,388,277,370,389,370,276,390,391,392,392,281,367,390,367,280,393,394,395,394,278,369,395,369,277,396,397,398,397,373,274,396,275,373,399,400,401,401,372,275,399,275,371,402,403,404,403,273,375,402,376,273,405,406,407,407,331,319,405,319,330,408,409,410,409,273,374,408,375,273,411,412,413,413,373,275,411,275,372,414,415,416,415,279,368,416,368,278,417,418,419,418,274,373,417,374,274,420,421,422,422,369,278,420,278,368,423,424,425,425,273,376,423,376,272,426,427,428,428,284,365,426,365,283,429,430,431,431,371,276,429,276,370,432,433,434,433,272,376,432,377,272,435,436,437,436,300,345,437,345,299,438,439,440,439,282,366,440,366,281,441,442,443,442,315,335,441,336,315,444,445,446,445,316,334,444,335,316,447,448,449,449,345,301,447,301,344,450,451,452,452,272,378,450,378,271,453,454,455,455,367,281,453,281,366,456,457,458,458,379,271,456,271,378,459,460,461,460,357,295,461,295,351,459,351,357,462,463,464,463,338,312,462,313,338,465,466,467,466,357,294,465,295,357,468,469,470,469,270,379,468,380,270,471,472,473,472,366,282,473,282,365,474,475,476,476,381,270,474,270,380,477,478,479,478,285,364,479,364,284,480,481,482,481,289,361,480,362,289,483,484,485,484,272,377,483,378,272,486,487,488,488,364,285,486,285,363,489,490,491,491,382,269,489,269,381,492,493,494,493,363,285,492,286,363,495,496,497,497,283,365,495,365,282,498,499,500,500,287,363,498,363,286,501,502,503,502,359,291,501,292,359,504,505,506,506,268,382,504,382,267,507,508,509,508,362,287,507,288,362,510,511,512,512,289,362,510,362,288,513,514,515,514,267,382,513,383,267,516,517,518,518,343,304,516,304,342,519,520,521,520,327,324,521,324,325,519,325,327,522,523,524,524,267,383,522,383,266,525,526,527,527,290,360,525,360,289,528,529,530,530,357,351,528,351,356,531,532,533,532,384,265,533,265,383,531,383,384,534,535,536,536,291,359,534,359,290,537,538,539,538,322,329,539,329,321,540,541,542,542,274,374,540,374,273,543,544,545,545,359,292,543,292,358,546,547,548,548,324,328,546,328,323,549,550,551,550,265,266,551,266,383,549,383,265,552,553,554,554,294,358,552,358,293,555,556,557,556,294,357,555,358,294,558,559,560,560,344,303,558,303,343,561,562,563,563,356,351,561,351,355,564,565,566,564,354,352,567,568,569,569,315,336,567,336,314,570,571,572,571,296,349,572,349,295,573,574,575,574,297,348,575,348,296,576,577,578,577,264,265,578,265,384,576,384,264,579,580,581,580,298,347,581,347,297,582,583,584,584,355,352,582,352,354,585,586,587,587,280,368,585,368,279,588,589,590,590,351,295,588,295,350,591,592,593,592,317,333,591,334,317,594,595,596,596,370,277,594,277,369,597,598,599,598,289,360,597,361,289,600,601,602,601,337,313,600,314,337,603,604,605,604,301,345,605,345,300,606,607,608,607,310,339,606,340,310,609,610,611,611,293,358,609,358,292,612,613,614,614,365,284,612,284,364,615,616,617,616,302,344,617,344,301,618,619,620,619,276,371,620,371,275,621,622,623,622,303,344,623,344,302,624,625,626,625,307,341,624,342,307,627,628,629,628,304,343,629,343,303,630,631,632,632,348,297,630,297,347,633,634,635,634,263,384,635,384,262,633,262,263,636,637,638,637,305,342,638,342,304,639,640,641,641,349,296,639,296,348,642,643,644,643,342,305,642,306,342,645,646,647,647,307,342,645,342,306,648,649,650,650,346,299,648,299,345,651,652,653,652,261,262,653,262,385,651,385,261,654,655,656,655,341,307,654,308,341,657,658,659,659,341,308,657,308,340,660,661,662,661,340,308,660,309,340,663,664,665,665,310,340,663,340,309,666,667,668,667,355,351,668,351,352,666,352,355,669,670,671,671,311,339,669,339,310,672,673,674,673,382,268,672,269,382,675,676,677,677,327,325,678,679,680,679,311,338,678,339,311,681,682,683,683,312,338,681,338,311,684,685,686,685,379,270,684,271,379,687,688,689,688,260,261,689,261,385,687,385,260,690,691,692,691,324,327,690,328,324,693,694,695,695,338,313,693,313,337,696,697,698,697,329,323,698,323,328,699,700,701,701,350,295,699,295,349,702,703,704,703,381,269,702,270,381,705,706,707,707,337,314,705,314,336,708,709,710,709,260,385,710,385,386,708,386,260,711,712,713,712,384,385,713,385,262,711,262,384,714,715,716,715,368,280,716,280,367,717,718,719,719,347,298,717,298,346,720,721,722,722,333,317,720,317,332,723,724,725,725,332,318,723,318,331,726,727,728,727,290,359,726,360,290,729,730,731,731,316,335,729,335,315,732,733,734,733,323,329,734,329,322,735,736,737,736,287,362,735,363,287,738,739,740,740,317,334,738,334,316,741,742,743,742,299,346,743,346,298,744,745,746,746,330,320,744,320,329,747,748,749,748,321,329,749,329,320,750,751,752,751,318,332,752,332,317,753,754,755,754,259,260,755,260,386,753,386,259,756,757,758,757,320,330,758,330,319,759,760,761,760,319,331,761,331,318,762,763,764,763,259,386,764,386,258,765,766,767,766,263,264,767,264,384,765,384,263,267,504,505,267,505,268,268,673,674,268,674,269,269,703,704,269,704,270,270,685,686,270,686,271,266,522,523,266,523,267,266,550,549,266,549,265,265,577,576,265,576,264,264,766,765,264,765,263,263,633,635,263,635,262,262,652,651,262,651,261,261,688,687,261,687,260,260,754,753,260,753,259,258,764,763,258,763,386,258,764,762,258,762,259,386,710,709,386,709,385,385,712,711,385,711,384,384,531,533,384,533,383,382,514,515,382,515,383,316,738,739,316,739,317,271,450,451,271,451,272,272,423,424,272,424,273,273,540,541,273,541,274,317,752,750,317,750,318,318,761,759,318,759,319,319,758,756,319,756,320,320,749,747,320,747,321,321,539,537,321,537,322,322,734,732,322,732,323,313,601,602,313,602,314,312,463,464,312,464,313,311,681,682,311,682,312,310,669,670,310,670,311,309,663,664,309,664,310,308,661,662,308,662,309,314,567,568,314,568,315,315,729,730,315,730,316,352,668,667,352,667,351,350,588,589,350,589,351,349,699,700,349,700,350,348,639,640,348,640,349,347,630,631,347,631,348,346,717,718,346,718,347,345,648,649,345,649,346,344,447,448,344,448,345,343,558,559,343,559,344,342,516,517,342,517,343,341,625,626,341,626,342,340,657,658,340,658,341,339,607,608,339,608,340,352,564,565,352,565,353,307,655,656,307,656,308,306,645,646,306,646,307,305,643,644,305,644,306,304,638,636,304,636,305,303,629,627,303,627,304,301,617,615,301,615,302,302,623,621,302,621,303,300,605,603,300,603,301,299,437,435,299,435,300,298,743,741,298,741,299,294,466,467,294,467,295,296,575,573,296,573,297,297,581,579,297,579,298,295,572,570,295,570,296,289,525,526,289,526,290,288,510,511,288,511,289,287,508,509,287,509,288,286,498,499,286,499,287,290,534,535,290,535,291,291,502,503,291,503,292,292,609,610,292,610,293,293,552,553,293,553,294,380,474,475,380,475,381,381,489,490,381,490,382,285,493,494,285,494,286,284,479,477,284,477,285,283,426,427,283,427,284,282,495,496,282,496,283,281,440,438,281,438,282,280,390,391,280,391,281,279,585,586,279,586,280,278,416,414,278,414,279,277,395,393,277,393,278,276,389,387,276,387,277,275,620,618,275,618,276,274,397,398,274,398,275,353,565,566,353,566,354,354,582,583,354,583,355,355,561,562,355,562,356,356,528,529,356,529,357,357,556,557,357,557,358,358,543,544,358,544,359,359,727,728,359,728,360,361,481,482,361,482,362,360,598,599,360,599,361,362,736,737,362,737,363,363,486,487,363,487,364,364,612,613,364,613,365,366,453,454,366,454,367,365,473,471,365,471,366,367,716,714,367,714,368,379,469,470,379,470,380,378,456,457,378,457,379,377,484,485,377,485,378,376,433,434,376,434,377,323,546,547,323,547,324,368,420,421,368,421,369,369,594,595,369,595,370,370,429,430,370,430,371,371,399,400,371,400,372,372,411,412,372,412,373,373,418,419,373,419,374,374,409,410,374,410,375,375,403,404,375,404,376,338,679,680,338,680,339,337,693,694,337,694,338,336,705,706,336,706,337,335,442,443,335,443,336,334,445,446,334,446,335,333,592,593,333,593,334,332,720,721,332,721,333,331,723,724,331,724,332,330,405,406,330,406,331,329,744,745,329,745,330,328,698,696,328,696,329,326,675,676,326,676,327,325,677,675,325,675,326,325,521,520,325,520,324,327,691,692,327,692,328,221,222,351,169,170,299,220,221,350,168,169,298,219,220,349,167,168,297,218,219,348,166,167,296,217,218,347,165,166,295,216,217,346,164,165,294,215,216,345,163,164,293,129,130,259,214,215,344,162,163,292,213,214,343,161,162,291,212,213,342,160,161,290,211,212,341,159,160,289,210,211,340,158,159,288,209,210,339,157,158,287,208,209,338,156,157,286,207,208,337,155,156,285,206,207,336,257,129,258,154,155,284,205,206,335,256,257,386,153,154,283,204,205,334,255,256,385,152,153,282,203,204,333,254,255,384,151,152,281,202,203,332,253,254,383,150,151,280,201,202,331,252,253,382,149,150,279,200,201,330,251,252,381,148,149,278,199,200,329,250,251,380,147,148,277,198,199,328,249,250,379,146,147,276,197,198,327,248,249,378,145,146,275,196,197,326,247,248,377,144,145,274,195,196,325,246,247,376,143,144,273,194,195,324,245,246,375,142,143,272,193,194,323,244,245,374,141,142,271,192,193,322,243,244,373,140,141,270,191,192,321,242,243,372,139,140,269,190,191,320,241,242,371,138,139,268,189,190,319,240,241,370,137,138,267,188,189,318,239,240,369,136,137,266,187,188,317,238,239,368,135,136,265,186,187,316,237,238,367,134,135,264,185,186,315,236,237,366,133,134,263,184,185,314,235,236,365,132,133,262,183,184,313,234,235,364,131,132,261,182,183,312,233,234,363,130,131,260,181,182,311,232,233,362,180,181,310,231,232,361,179,180,309,230,231,360,178,179,308,229,230,359,177,178,307,228,229,358,176,177,306,227,228,357,175,176,305,226,227,356,174,175,304,225,226,355,173,174,303,224,225,354,172,173,302,223,224,353,171,172,301,51,52,181,0,1,130,103,104,233,52,53,182,1,2,131,104,105,234,53,54,183,2,3,132,105,106,235,54,55,184,3,4,133,106,107,236,55,56,185,4,5,134,107,108,237,56,57,186,5,6,135,108,109,238,57,58,187,6,7,136,109,110,239,58,59,188,7,8,137,110,111,240,59,60,189,8,9,138,111,112,241,60,61,190,9,10,139,112,113,242,61,62,191,10,11,140,113,114,243,62,63,192,11,12,141,114,115,244,63,64,193,12,13,142,115,116,245,64,65,194,13,14,143,116,117,246,65,66,195,14,15,144,117,118,247,66,67,196,15,16,145,118,119,248,67,68,197,16,17,146,119,120,249,68,69,198,17,18,147,120,121,250,69,70,199,18,19,148,121,122,251,70,71,200,19,20,149,122,123,252,71,72,201,20,21,150,123,124,253,72,73,202,21,22,151,124,125,254,73,74,203,22,23,152,125,126,255,74,75,204,23,24,153,126,127,256,75,76,205,24,25,154,127,128,257,76,77,206,25,26,155,128,0,129,77,78,207,26,27,156,78,79,208,27,28,157,79,80,209,28,29,158,80,81,210,29,30,159,81,82,211,30,31,160,82,83,212,31,32,161,83,84,213,32,33,162,84,85,214,33,34,163,85,86,215,34,35,164,86,87,216,35,36,165,87,88,217,36,37,166,88,89,218,37,38,167,89,90,219,38,39,168,90,91,220,39,40,169,91,92,221,40,41,170,92,93,222,41,42,171,93,94,223,42,43,172,94,95,224,43,44,173,95,96,225,44,45,174,96,97,226,45,46,175,97,98,227,46,47,176,98,99,228,47,48,177,99,100,229,48,49,178,100,101,230,49,50,179,101,102,231,50,51,180,102,103,232,170,171,300,222,223,352,388,387,277,389,388,370,392,391,281,390,392,367,394,393,278,395,394,369,397,396,373,396,398,275,401,400,372,399,401,275,403,402,273,402,404,376,407,406,331,405,407,319,409,408,273,408,410,375,413,412,373,411,413,275,415,414,279,416,415,368,418,417,274,417,419,374,422,421,369,420,422,278,425,424,273,423,425,376,428,427,284,426,428,365,431,430,371,429,431,276,433,432,272,432,434,377,436,435,300,437,436,345,439,438,282,440,439,366,442,441,315,441,443,336,445,444,316,444,446,335,449,448,345,447,449,301,452,451,272,450,452,378,455,454,367,453,455,281,458,457,379,456,458,271,460,459,357,461,460,295,459,461,351,463,462,338,462,464,313,466,465,357,465,467,295,469,468,270,468,470,380,472,471,366,473,472,282,476,475,381,474,476,270,478,477,285,479,478,364,481,480,289,480,482,362,484,483,272,483,485,378,488,487,364,486,488,285,491,490,382,489,491,269,493,492,363,492,494,286,497,496,283,495,497,365,500,499,287,498,500,363,502,501,359,501,503,292,506,505,268,504,506,382,508,507,362,507,509,288,512,511,289,510,512,362,514,513,267,513,515,383,518,517,343,516,518,304,520,519,327,521,520,324,519,521,325,524,523,267,522,524,383,527,526,290,525,527,360,530,529,357,528,530,351,532,531,384,533,532,265,531,533,383,536,535,291,534,536,359,538,537,322,539,538,329,542,541,274,540,542,374,545,544,359,543,545,292,548,547,324,546,548,328,550,549,265,551,550,266,549,551,383,554,553,294,552,554,358,556,555,294,555,557,358,560,559,344,558,560,303,563,562,356,561,563,351,564,566,354,569,568,315,567,569,336,571,570,296,572,571,349,574,573,297,575,574,348,577,576,264,578,577,265,576,578,384,580,579,298,581,580,347,584,583,355,582,584,352,587,586,280,585,587,368,590,589,351,588,590,295,592,591,317,591,593,334,596,595,370,594,596,277,598,597,289,597,599,361,601,600,337,600,602,314,604,603,301,605,604,345,607,606,310,606,608,340,611,610,293,609,611,358,614,613,365,612,614,284,616,615,302,617,616,344,619,618,276,620,619,371,622,621,303,623,622,344,625,624,307,624,626,342,628,627,304,629,628,343,632,631,348,630,632,297,634,633,263,635,634,384,633,635,262,637,636,305,638,637,342,641,640,349,639,641,296,643,642,342,642,644,306,647,646,307,645,647,342,650,649,346,648,650,299,652,651,261,653,652,262,651,653,385,655,654,341,654,656,308,659,658,341,657,659,308,661,660,340,660,662,309,665,664,310,663,665,340,667,666,355,668,667,351,666,668,352,671,670,311,669,671,339,673,672,382,672,674,269,677,676,327,679,678,311,678,680,339,683,682,312,681,683,338,685,684,379,684,686,271,688,687,260,689,688,261,687,689,385,691,690,324,690,692,328,695,694,338,693,695,313,697,696,329,698,697,323,701,700,350,699,701,295,703,702,381,702,704,270,707,706,337,705,707,314,709,708,260,710,709,385,708,710,386,712,711,384,713,712,385,711,713,262,715,714,368,716,715,280,719,718,347,717,719,298,722,721,333,720,722,317,725,724,332,723,725,318,727,726,290,726,728,360,731,730,316,729,731,335,733,732,323,734,733,329,736,735,287,735,737,363,740,739,317,738,740,334,742,741,299,743,742,346,746,745,330,744,746,320,748,747,321,749,748,329,751,750,318,752,751,332,754,753,259,755,754,260,753,755,386,757,756,320,758,757,330,760,759,319,761,760,331,763,762,259,764,763,386,766,765,263,767,766,264,765,767,384,
  };

float vertices_G[SYMBOL_2D_POINT_COUNT * 3 * 2];
unsigned int indices_G[SYMBOL_2D_TRIANGLE_COUNT * 3 * 2 + (SYMBOL_2D_POINT_COUNT * 3 * 2)];
get_symbol_points(vertices_G, SYMBOL_2D_POINT_COUNT * 3 * 2, indices_G, SYMBOL_2D_TRIANGLE_COUNT * 3 *2 + (SYMBOL_2D_POINT_COUNT * 3 * 2), 0.1f);



//------------------------------------------------------------
    unsigned int VAO[NUMBER_LETTERS];
    glGenVertexArrays(NUMBER_LETTERS, VAO);

	unsigned int VBO[NUMBER_LETTERS];
    glGenBuffers(NUMBER_LETTERS, VBO);

	unsigned int EBO[NUMBER_LETTERS];
    glGenBuffers(NUMBER_LETTERS, EBO);

	unsigned int EBOindices[NUMBER_LETTERS];
    glGenBuffers(NUMBER_LETTERS, EBOindices);
	


    // uncomment this call to draw in wireframe polygons.
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//-------------------------------LETTER BETA-----------------------------

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_beta), vertices_beta, GL_STATIC_DRAW);

//    Element buffer OBJECT

    glBindBuffer(GL_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_beta), color_beta, GL_STATIC_DRAW);

//    Element buffer OBJECT
  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindices[0]);
  	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_beta), indices_beta, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(
		0,            // attribute. No particular reason for 0, but
		              // must match the layout in the shader.
		3,            // size
		GL_FLOAT,     // type
		GL_FALSE,     // normalized?
		0,            // stride
		(void*)0      // array buffer offset
	);

	// 2nd attribute buffer : color
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, EBO[0]);
	glVertexAttribPointer(
		1,            // attribute. No particular reason for 1, but
		              // must match the layout in the shader.
		3,            // size
		GL_FLOAT,     // type
		GL_FALSE,     // normalized?
		0,            // stride
		(void*)0      // array buffer offset
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindices[0]);
	// glVertexAttribPointer(
	// 	2,            // attribute. No particular reason for 1, but
	// 	              // must match the layout in the shader.
	// 	3,            // size
	// 	GL_FLOAT,     // type
	// 	GL_FALSE,     // normalized?
	// 	0,            // stride
	// 	(void*)0      // array buffer offset
	// );

//------------------------------LETTER G------------------------------

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_G), vertices_G, GL_STATIC_DRAW);

//    Element buffer OBJECT

    // glBindBuffer(GL_ARRAY_BUFFER, EBO[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(color_beta), color_beta, GL_STATIC_DRAW);

//    Element buffer OBJECT
  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindices[1]);
  	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_G), indices_G, GL_STATIC_DRAW);


		// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(
		0,            // attribute. No particular reason for 0, but
		              // must match the layout in the shader.
		3,            // size
		GL_FLOAT,     // type
		GL_FALSE,     // normalized?
		0,            // stride
		(void*)0      // array buffer offset
	);

	// 2nd attribute buffer : color
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, EBO[1]);
	glVertexAttribPointer(
		1,            // attribute. No particular reason for 1, but
		              // must match the layout in the shader.
		3,            // size
		GL_FLOAT,     // type
		GL_FALSE,     // normalized?
		0,            // stride
		(void*)0      // array buffer offset
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindices[1]);

//-----------------------------------------------------------------------


// build and compile our shader program
      // ------------------------------------
      // vertex shader
      unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
      glCompileShader(vertexShader);
      // check for vertex shader compile errors
      int success;
      char infoLog[512];
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
          glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
          std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      }
      // fragment shader
      unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
      glCompileShader(fragmentShader);
      // check for fragment shader compile errors
      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
          glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
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
          glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
          std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      }
      
      // delete shaders, we don't need them anymore
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);




  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    //input
    //.....
    processInput(window);



    // render
    // ------

     // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    // glBindVertexArray(VBO);



// Get a handle for our "MVP" uniform
      unsigned int MatrixID = glGetUniformLocation(shaderProgram, "MVP");

	  // Model matrix : an identity matrix (model will be at the origin)
      glm::mat4 Model = glm::mat4(1.0f);
	  Model = glm::rotate(Model, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0)); //roda segundo o eixo dos yy
	
	  // View camera matrix
      glm::mat4 View = glm::lookAt(
                      cameraPos, //in World Space
                      cameraFront, // and looks at the origin
                      cameraUp // Head 
          );


      // Projection matrix : 45 Field of View, 4:3 ratio,
      // display range : 0.1 unit <-> 100 units
     // glm::mat4 Projection = glm::perspective(glm::radians(30.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	  glm::mat4 Projection = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,0.1f,100.0f); // In world coordinates

    
      
	  // Our ModelViewProjection : multiplication of our 3 matrices
      // Remember, matrix multiplication is the other way around
      glm::mat4 MVP   = Projection * View * Model; 
      


   // Send our transformation to the currently bound shader, 
      // in the "MVP" uniform
      

    //------------------------------------------------------------


        // Enable depth test
          glEnable(GL_DEPTH_TEST);  
          // Accept fragment if it closer to the camera than the former one
          glDepthFunc(GL_LESS); 

          // also clear the depth buffer now!
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
          
       
        // seeing as we only have a single VAO there's no need to bind
        // it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        // glBindVertexArray(0); // no need to unbind it every time 

	glBindVertexArray(VAO[0]);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0][0]);
    glDrawElements(GL_TRIANGLES, sizeof(indices_beta) / sizeof(float), GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO[1]);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[1][0][0]);
    glDrawElements(GL_TRIANGLES, sizeof(indices_G) / sizeof(float), GL_UNSIGNED_INT, 0);


	

    /* glfw: swap buffers and poll IO events (keys pressed/released, 
	 mouse moved etc.)
	 --------------------------------------------------------------*/
    //cria janela e processa tudo o que nela se passa
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO[0]);
  glDeleteBuffers(1, &VBO[0]);
  glDeleteBuffers(1, &EBO[0]);
  glDeleteBuffers(1, &EBOindices[0]);


  glDeleteProgram(shaderProgram);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}
