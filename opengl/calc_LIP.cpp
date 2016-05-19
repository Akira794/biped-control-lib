#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

double z = 0.8;		// �����ʒu����
double x =  0.15;	// �����ʒu��
double f = 0.0;		//�R���
const double m = 10.00;	//�d��kg
const double dt = 0.01;	//�C���^�[�o��
const double g = 9.8; 	//�d�͉���m/s^2

double v_x = -0.46;	//�����x�y��x�����̑��x



void display(void)		//�f�B�X�v���C�̕\��
{
	double roll_x;
	double roll_y;
	double deg;
	double rad = 0;
	double arg = 0.0;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);
	glEnd();

	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex2d(30*x, 30*z);
	glVertex2d(0, 0);
	glEnd();
	glTranslatef(30*x, 30*z, 0);
	glRotatef(arg, 0.0, 0.0, 1.0);

	while(1){
		deg = deg + 1;
		rad = deg * M_PI/180;

		roll_x = sin(rad);
		roll_y = cos(rad);

		glRectf(1*roll_x, 1*roll_y, 0.0, 0.0);
		if(deg == 360)break;
	}
	glPopMatrix();

	glutSwapBuffers();
}

void simu(void)			//���ȏ�p104~112�܂ł̓��e
{
	double E = 0.0;		//�O���G�l���M�[
	double v = 0.0;		//�u�Ԃ̑��x
	double x_a = 0.0;	//�u�Ԃ̈ʒu

	double a_z = 0.0;	//�������̉����x
	double v_z = 0.0;	//�������̑��x

	const double F = -m * g;	//�d��

	double a_x = 0.0;	//�������̉����x

	double s;			//�|���U�q�̉�]�p
	s = atan(x / z) * 180/M_PI;
	printf("s:%lf \n",s);

	if( -60 < s && s < 60 ){
		s = s * M_PI/180;

		f = m * g /cos(s);		//�R��͂̐ݒ� (4.2)

		a_z = (f*cos(s)+F) / m;		//�������̉^�� (4.3)
		v_z += a_z * dt;
		z += v_z *dt;

		a_x = f*sin(s) / m;		//�������̉^��
		v_x += a_x * dt;
		x += v_x *dt;
	}

	glutPostRedisplay();

	E = (v_x*v_x)/2-(g*x*x)/(2*z);		//�O���G�l���M�[�̌v�Z (4.11)

	printf("---Orbital energy---/%lf/------\n", E);

	/*�O���G�l���M�[���r���ă|�e���V�����̎R���z���邩
	over-�z�����ꍇ�@�@under-�z���Ȃ�
	p112�̓��e���v�Z����B*/

	if(E > 0){
		printf("---potential <<< over >>>\n");
		v = 2*E;
		v = sqrt(v);
		printf("---v----/%lf/----------\n", v);
	}
	else if(E <= 0){
		printf("---potential <<< under >>>\n");
		x_a = -(2*z*E)/g;
		x_a = sqrt(x_a);
		printf("---x_a-----/%lf/------------\n", x_a);
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
	glViewport( 0, 0, 300, 300 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case '\x1b':
			exit(0);
			break;
	}
}


void mouse(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if ( state == GLUT_DOWN)
				glutIdleFunc(simu);
			break;

		case GLUT_RIGHT_BUTTON:
			if ( state == GLUT_DOWN){
				glutIdleFunc(NULL);
				exit(0);
			}break;
		default:
			break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (300, 300);
	glutInitWindowPosition (1000, 100);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

