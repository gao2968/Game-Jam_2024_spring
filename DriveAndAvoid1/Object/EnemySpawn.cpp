#include "EnemySpawn.h"
#include "DxLib.h"

// �z������������G
E_NUM E_Spawn::data[63];
int E_Spawn::row;

// �R���X�g���N�^
E_Spawn::E_Spawn()
{
	int fp;
	char buf[100];	// ������ǂݎ��p
	char c;			// �������ЂƂÂ��ǂ��Ă������߂̕ϐ�
	int col = 1;	// csv�t�@�C���̗�
	row = 0;		// csv�t�@�C���̍s
	int count = 0;	// ���������邽�߂�1�����Â��炵�Ă���

	// �z����̂��ׂĂ�0�Ŗ��߂�
	memset(buf, 0, sizeof(buf));

	// �t�@�C���̃��[�h
	if (fp = FileRead_open("Resource/dat/Enemys_Data.csv"));


	// 1�s�ڂ𖳎����� �t�@�C������P�����擾���邽�߂̕ϐ�
	while (FileRead_getc(fp) != '\n');

	// �f�[�^�̓ǂݍ��� ����while�Q�͖������[�v
	while (true) {
		while (true) {

			// �t�@�C����1�������擾���J��Ԃ��A������ɂ���
			c = FileRead_getc(fp);
			buf[count] = c;

			// �J���}�A���s�AEOF�Ȃ烋�[�v�𔲂���
			if (c == ',' || c == '\n' || c == EOF) {
				buf[count] = '\0';
				break;
			}
			count++;
		}

		// ��̈ʒu�Ő��l������
		// atoi�͌^��ύX���Ă����֐�
		// float�Ȃ�float�ɁAint�Ȃ�int�ɂ��Ă����

		switch (col) {

			// X���W
		case 1:

			data[row].location_x = atoi(buf);
			break;

			// Y���W
		case 2:
			data[row].location_y = atoi(buf);
			break;

			// ���a
		case 3:
			data[row].radius = atoi(buf);
			break;

			// �G�X�s�[�h
		case 4:
			data[row].speed = atoi(buf);
			break;

			// �e�̃X�s�[�h
		case 5:
			data[row].bullet_speed = atoi(buf);
			break;

			// �X�R�A
		case 6:
			data[row].score = atoi(buf);
			break;

			// HP
		case 7:
			data[row].hp = atoi(buf);
			break;

			// �o������
		case 8:
			data[row].time = atoi(buf);
			break;
		}
		// ����������	buf���܂�0�Ŗ��߂Ă���
		memset(buf, 0, sizeof(buf));

		// EOF�Ȃ�out�ɔ��
		// EOF���Ȃ�����i���Ƀ��[�v����
		if (c == EOF) {
			goto out;
		}

		// EOF�ʂ�Ȃ������Ȃ�ǂݍ��ވʒu�����������Ď��̗��ǂ�
		count = 0;
		col++;

		// ���s�Ȃ玟�̍s�ɍs��
		if (c == '\n') {
			col = 1;
			++row;
		}
		// �܂����[�v�̈�ԏ��߂ɖ߂�
	}
	// �B��̃��[�v�o���͂���
out:
	FileRead_close(fp);
}


E_Spawn::~E_Spawn()
{

}

// �G���̓ǂݍ���
E_NUM E_Spawn::LoadEnemy(int i)
{
	return data[i];
}

// �ǂݍ��܂ꂽ�G�̗ʂ̎擾
int E_Spawn::GetMaxEnemy()
{
	// �s����Ԃ����ƂŔ��f �����������ꂽ�s���J�E���g���Ă���̂�-1
	return row - 1;
}
