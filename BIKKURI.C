/*
 * n!(N|n<=100)を計算する  [ bikkuri.c ]  Ver0.70
 *                                      1990/06/13
 */

static char sccsid[] = "@(#)bikkuri.c   0.70    (UME20)    06/13/90";

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		K_KOTAE		100			/* 答えの最大桁／２ */

/********************************************************************
 ******* 関数プロトタイプ *******************************************
 *******************************************************************/

/******* main ******************************************************/
unsigned int	n_check(int, char *[]);

/******* ooboke ****************************************************/
void	ojiisan(void);
void	opening(void);
void	dounyuu(void);
void	sekikom(void);
void	macigai(unsigned int [],unsigned int,unsigned int *);
void	disp_detarame(unsigned int[],unsigned int);
void	hit_any_key(void);

/******* majime ****************************************************/
void	n_kaijo(unsigned int);

/******* pablic ****************************************************/
void	dekasugi(void);
void	kake(unsigned int [],unsigned int,unsigned int *);
void	disp_kai(unsigned int []);

/********************************************************************
 ******* メイン関数 *************************************************
 *******************************************************************/
main(int argc, char *argv[])
{
	unsigned int	n;
	
	n = n_check(argc,argv);
	if(n == 0) {
		ojiisan();
	} else {
		n_kaijo(n);
	}
}

/******* 引数チェック (from main) **********************************/
unsigned int	n_check(int argc, char *argv[])
{
	int	n;
	
	if(argc == 1) {
		n = 0;
	} else {
		n = atoi(*(++argv));
		if((n < 0) || (n > 100)){
			puts("\nそんな数の階乗など，できんわい．");
			exit(1);
		}
		if(n == 0) {
			puts("\n０の階乗は１なのじゃ．");
			exit(0);
		}
		if(n == 1) {
			puts("\n１の階乗は１なのじゃ．");
			exit(0);
		}
	}
	return(n);
}

/********************************************************************
 ******* ネバーエンディング階乗（引数無しの場合） *******************
 *******************************************************************/
void	ojiisan(void)
{
	static unsigned int		kai[K_KOTAE];	/* 階乗の答 */
	unsigned int	keta;					/* 桁数 */
	unsigned int	i;						/* ループカウンタ */
	
	opening();
	dounyuu();
	kai[0] = 1;
	keta = 0;
	for(i = 2; ; i++) {
		printf("そして，");
		disp_kai(kai);
		printf("に %d をかけると",i);
		kake(kai,i,&keta);
		disp_kai(kai);
		printf("になるんぢゃ．");
		if(i == 37) {				/* イベント１ 間違い */
			macigai(kai,++i,&keta);
		}
		if(i == 71) {				/* イベント２ 咳き込む */
			sekikom();
		}
	}
}

/******* 物語のはじまり，はじまりぃ…… ****************************/
void	opening(void)
{
	puts("孫　「ねぇねぇ，おじいちゃん．」");
	puts("老人「なんぢゃ？」\n");
	hit_any_key();
	puts("孫　「“階乗”ってなーに？」");
	puts("老人「ああ，会を開く場所のことぢゃよ」");
	puts("孫　「それは“会場”」");
	puts("老人「ん？　なら，身体の重さのことぢゃ．」");
	puts("孫　「それは“体重”！」");
	puts("老人「ラドンとかキングギドラの事かの？」");
	puts("孫　「それは“怪獣”！」");
	puts("老人「もっとも優れておる……」");
	puts("孫　「それは“最上”」");
	puts("老人「秘密，秘密．」");
	puts("孫　「“内緒”！」");
	puts("老人「男の……」");
	puts("孫　「“甲斐性”！」");
	puts("老人「インスタントラーメン」");
	puts("孫　「“うまいっしょ”」 \n");
	puts("老人「……」");
	puts("孫　「……」\n");
	hit_any_key();
	puts("老人，孫「どうも しつれーしやしたー！！！！」\n");
	hit_any_key();
	puts("孫　「そーじゃなくってー！」");
	puts("老人「わかっとるよ，“階乗”ぢゃろう？");
	puts("　　　ｎの階乗ってのはだなぁ，ｎ！ってことじゃ」");
	puts("孫　「そんなんじゃ，わかんないよぉ．」");
	puts("老人「要するに１掛ける２掛ける３掛ける……と，");
	puts("　　　どんどん掛けていく事なのぢゃ．」");
	puts("孫　「ふーん．」\n");
	hit_any_key();
}

/******* 階乗計算始めの導入部分 ************************************/
void	dounyuu(void)
{
	puts("老人「具体的に言うとな，");
	puts("　　　まず，０の階乗は１なんじゃ．」");
	puts("孫　「エー，どーしてー？　０じゃないのー？」");
	puts("老人「どーしても！　そーゆーふーに，決っとるんぢゃ」");
	puts("孫　「フーン……」");
	puts("老人「で，１の階乗も１なんぢゃ．これは解るじゃろ．」");
	puts("孫　「うん．」\n");
	hit_any_key();
	printf("老人「");
}

/******* おもわず咳き込んでしまう **********************************/
void	sekikom(void)
{
	puts("　……げほっ げほっ げほっ」\n");
	puts("孫　「おじいちゃん，大丈夫？」");
	puts("老人「……み……水をくれ……．」");
	puts("孫　「み……みず？」");
	puts("老人「言っとくが，ミミズじゃないぞ．」");
	puts("孫　「（あはっ，バレちゃった！）");
	puts("　　        　…………はーい，お水！」");
	puts("老人「ゴクッゴクッ……ふぅ．さて，と，続きを話そうかな\n");
	hit_any_key();
}

/******* 間違えて孫に指摘されてしまう ******************************/
void	macigai(unsigned int kai[],unsigned int i,unsigned int *keta)
{
	printf("そして，");
	disp_kai(kai);
	printf("に %d をかけると",i);
	disp_detarame(kai,i);
	puts("になるんぢゃよ．」");
	puts("孫　「……えっ？ちょっと，おじいちゃん．」");
	hit_any_key();
	puts("老人「何じゃ？」");
	hit_any_key();
	printf("孫　「");
	disp_kai(kai);
	printf("に %d をかけたら",i);
	kake(kai,i,keta);
	disp_kai(kai);
	puts("になるよー．」");
	puts("老人「おお，そういう言い方もあるな．まぁ細かいことは気にせんと．」");
	puts("孫　「全くぅ，おじいちゃん，いい加減なんだから……」\n");
	hit_any_key();
	printf("老人「さて続きをやろうかな．");
}

/******* でたらめな答えの表示 **************************************/
void	disp_detarame(unsigned int kai[],unsigned int i)
{
	unsigned int	j,rei;
	
	rei = 0;
	for(j = 0; j < K_KOTAE; j++) {
		if(rei == 0) {
			if(kai[K_KOTAE-j-1] == 0) {
				continue;
			} else {
				printf("%u",kai[K_KOTAE-j-1]*i);
				rei = 1;
			}
		} else {
			printf("%02u",rand()/328);
		}
	}
}

/******* 何かのキーを押してください ********************************/
void	hit_any_key(void)
{
	fputs("\33[47m--hit any key--\33[m",stdout);
	getch();
	fputs("\r                \r",stdout);
}

/********************************************************************
 ******* ｎまで階乗（引数ありの場合） *******************************
 *******************************************************************/
void	n_kaijo(unsigned int n)
{
	static unsigned int		kai[K_KOTAE];	/* 階乗の答 */
	unsigned int	keta;					/* 桁数 */
	unsigned int	i;						/* ループカウンタ */
	
	printf("ほう，%d の階乗が知りたいのか．\n",n);
	puts("よーし，待っとれ．\n");
	kai[0] = 1;
	keta = 0;
	for(i = 2; i <= n; i++) {
		printf("\r今 %d を計算しておるところじゃ．",i);
		kake(kai,i,&keta);
	}
	puts("\n\n待たせたな．計算が終ったぞ．");
	puts("答えはこうぢゃ．");
	disp_kai(kai);
	puts("\n\nどうじゃ，ためになったろう．");
	exit(0);
}

/********************************************************************
 ******* おじいさん＆階乗 共用 サブ関数 *****************************
 *******************************************************************/

/******* 積算的乗算（我思引数型名是過長(笑)） **********************/
void	kake(unsigned int kai[],unsigned int i,unsigned int *keta)
{
	unsigned int	j,kuri;
	
	kuri = 0;
	for(j = 0; j < K_KOTAE; j++) {
		if(j > *keta) {
			if(kuri == 0) {
				break;
			} else {
				(*keta)++;
			}
		}
		kai[j] = kai[j] * i + kuri;
		if(kai[j] >= 100) {
			if(j == K_KOTAE - 1) {
				dekasugi();
			}
			kuri   = kai[j] / 100;
			kai[j] = kai[j] % 100;
		} else {
			kuri = 0;
		}
	}
}

/******* 答えが大きくなりすぎた ************************************/
void	dekasugi(void)
{
	puts("\a……おや，答えが大きくなりすぎおった．\n");
	puts("こりゃぁもう，わしの手にはおえんわい．");
	puts("すまんこったのぉ．\n");
	puts("ふぉっふぉっふぉっふぉ");
	exit(1);
}

/******* kai[]の表示 ***********************************************/
void	disp_kai(unsigned int kai[])
{
	unsigned int	i,rei;
	
	rei = 0;
	for(i = 0; i < K_KOTAE; i++) {
		if(rei == 0) {
			if(kai[K_KOTAE-i-1] == 0) {
				continue;
			} else {
				printf("%u",kai[K_KOTAE-i-1]);
				rei = 1;
			}
		} else {
			printf("%02u",kai[K_KOTAE-i-1]);
		}
	}
}
