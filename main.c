#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASSSIZE			35 // SINIFKAPASITE
#define STUDENTNUMBERLENGTH 10 // OGRENCINUMARAUZUNLUGU
#define NAMELENGTH			25 // ADIUZUNLUGU
#define COURSENAMELENGTH	50 // DERSADIUZUNLUGU
#define COURSECODELENGTH	10 // DERSKODUZUNLUGU
#define COURSESREGISTERED	5  // KAYITLIDERSLER
#define MIDTERMWEIGHT		30 // VIZEAGIRLIK
#define FINALWEIGHT			30 // FINALAGIRLIK
#define QUIZWEIGHT			20 // QUIZAGIRLIK
#define HOMEWORKWEIGHT		20 // ODEVAGIRLIK
#define MAXCOURSESIZE		20 // MAKSKURSKAPASITE
#define MAXSTUDENTSIZE		400 // MAKSOGRENCIKAPASITE

typedef struct fullName{		//tam adi
	char *name;					//adi
	char *surname;				//soyadi
}name_t;

typedef struct examGrades{		//sinav not
	double midterm;				//vize
	double final;				//final
	double quiz;				//quiz
	double homework;			//odev
}grades_t;

typedef struct courseRegistered{		//kayitliDersler
	char courseName[COURSENAMELENGTH];	//ders adi
	char courseCode[COURSECODELENGTH];	//ders kodu
	grades_t grades;					//notler
	char letterGrade[2];				//herf notu
	double numericGrade;				//numerik notu
}courseReg_t;

typedef struct studentInfo{						//ogrenci bilgi
	name_t studentName;							//ogrenci adi
	char *stNo;									//ogrenci numara
	courseReg_t courses[COURSESREGISTERED];		//dersler
	double gpa;									//ortalama
}student_t;

typedef struct courseInfo{						//ders bilgi
	char courseName[COURSENAMELENGTH];			//ders adi
	char courseCode[COURSECODELENGTH];			//ders kodu
	student_t students[CLASSSIZE];				//ogrenciler
	double courseAverage;						//ders ortalama
}courses_t;




int findStudent(student_t *s, char *st);				// girilen ogrenci numarasina gore dizide uygun ogrenciyi bulan fonksiyon
int findCourse(courses_t *c, char *code);				// girilen ders koduna gore dizide uygun dersi bulan fonksiyon

double calculateStudentGPA(student_t s);				// verilen ogrencinin butun derslerinin notlarinin ortalamasi
double calculateCourseAverage(courses_t	c);				// verilen dersin butun ogrencilerinin notlarinin ortalamasi

void calculateStudentCourseGrade(courseReg_t *r);		// verilen kayita gore ogrencinin kayitli oldugu dersin notunun hesaplanmasi

void displayStudentInfo(student_t s);					// verilen ogrencinin bilgilerini gosteren fonksiyon
void displayCourseInfo(courses_t c);					// verilen dersin bilgilerini gosteren fonksiyon
void printClass(courses_t c);							// verilen dersin ogrencilerini yazdiran program
void printMenu();										// statik Menuyu bastiran fonksiyon

courses_t addCourse();									// Ders ekleme 
student_t addStudent();									// Ogrenci ekleme
courseReg_t registerCourse();							// Kayit ekleme 








int findStudent(student_t *s, char *st)				// girilen ogrenci numarasina gore dizide uygun ogrenciyi bulan fonksiyon
{
	int i = 0;
	for(i = 0 ; i < MAXSTUDENTSIZE; i++)			// butun ogrencileri kontrol ede bilmek icin 0-dan MAXSTUDENTSIZE-a kadar for dongusunde kaliyoruz.
	{
		if(strcmp(s[i].stNo, st) == 0)				// strcmp() fonksiyonu girdi olarak verilen iki string esitse 0 dondurur.
		{
			return i; 								// eger aradigimiz oyrenciyi bulduysak bunun dizide kacinci eleman oldugunu donderiyoruz.
		}
	}

	return -1;										// eger aradigimiz numarayi bulamadiysak -1 donderiyoruz ki bulunamadigini anlayalim.
}

int findCourse(courses_t *c, char *code)			// girilen ders koduna gore dizide uygun dersi bulan fonksiyon
{
	int i = 0;
	for(i = 0 ; i < MAXCOURSESIZE; i++)				// butun dersleri kontrol ede bilmek icin 0-dan MAXCOURSESIZE-a kadar for dongusunde kaliyoruz.
	{
		if(strcmp(c[i].courseCode, code) == 0)		// strcmp() fonksiyonu girdi olarak verilen iki string esitse 0 dondurur.
		{
			return i; 								// eger aradigimiz dersi bulduysak bunun dizide kacinci eleman oldugunu donderiyoruz.
		}
	}

	return -1;										// eger aradigimiz kodu bulamadiysak -1 donderiyoruz ki bulunamadigini anlayalim.
}






double calculateStudentGPA(student_t s)					// verilen ogrencinin butun derslerinin notlarinin ortalamasi
{
	int i = 0;
	double sum = 0;										// notlarin toplamini tutacak degisken

	for(i = 0; s.courses[i].courseName[0] != 42; i++)	// ogrencinin kayitli oldugu dersin isminin ilk harfi "*" ise bostur.
		sum += s.courses[i].numericGrade;				// kayitli oldugu dersin notunu toplama ekliyoruz
	
	if(i == 0) return 0;								// eger i 0-a esitse 0 donderiyoruz aksi halde 0-a bolme sorunu cikacakti
	else return sum / i;								// toplami kayitli oldugu ders sayina bolup ortalamayi buluyoruz.
}

double calculateCourseAverage(courses_t	c)				// verilen dersin butun ogrencilerinin notlarinin ortalamasi
{
	int i = 0;

	while(c.students[i].stNo != NULL) i++; 				// derse kayitli ogrencilerin sayini bulmak icin ogrenci numarasi NULL olana kadar i-yi arttiriyoruz.
	
	if(i == 0) return 0;								// eger i 0-a esitse 0 donderiyoruz aksi halde 0-a bolme sorunu cikacakti
	else return c.courseAverage / i;					// main fonksiyonda ogrenci kayit ettikce notunu da courseAverage degiskenine ekliyoduk
														// yani courseAverage aslinda toplami tutuyor.
}









void calculateStudentCourseGrade(courseReg_t *r)		// verilen kayita gore ogrencinin kayitli oldugu dersin notunun hesaplanmasi
{
	double grade = (MIDTERMWEIGHT * r->grades.midterm + FINALWEIGHT * r->grades.final 
					+ HOMEWORKWEIGHT * r->grades.homework + QUIZWEIGHT * r->grades.quiz) / 100.00;

	// basit matematik ile son notu buluyoruz ve bu nota gore puan veriyoruz.
	
	if(grade > 89)
	{
		strcpy(r->letterGrade, "AA");
		r->numericGrade = 4.00;
	} else if(grade > 84)
	{
		strcpy(r->letterGrade, "BA");
		r->numericGrade = 3.50;
	} else if(grade > 79)
	{
		strcpy(r->letterGrade, "BB");
		r->numericGrade = 3.00;
	} else if(grade > 74)
	{
		strcpy(r->letterGrade, "CB");
		r->numericGrade = 2.50;
	} else if(grade > 69)
	{
		strcpy(r->letterGrade, "CC");
		r->numericGrade = 2.00;
	} else if(grade > 59)
	{
		strcpy(r->letterGrade, "DC");
		r->numericGrade = 1.50;
	} else if(grade > 49)
	{
		strcpy(r->letterGrade, "DD");
		r->numericGrade = 1.00;
	} else 
	{
		strcpy(r->letterGrade, "FF");
		r->numericGrade = 0.00;
	}
}












void displayStudentInfo(student_t s)																// verilen ogrencinin bilgilerini gosteren fonksiyon
{
	int i = 0;

	printf("\nStudent No: %s\n", s.stNo);															// ogrenci numarasini bastiriyoruz
	printf("Student Fullname: %s %s\n\n", s.studentName.name, s.studentName.surname);				// ogrenci isim ve soyimini bastiriyoruz

	if (s.courses[0].courseName[0] != 42)															// ogrencinin kayitli oldugu dersin isminin ilk harfi "*" ise bostur.
	{
		printf("Registered Courses: \n\n");

		for (i = 0; s.courses[i].courseName[0] != '*'; i++) 									// bos olana kadar butun kayitli dersleri yazdiriyoruz
		{
			printf("Course Code: %s\n", s.courses[i].courseCode);									// ders kodu
			printf("Course Name: %s\n", s.courses[i].courseName);									// ders ismi
			printf("Grade: %s (%.2f)\n\n", s.courses[i].letterGrade, s.courses[i].numericGrade);	// ders notu
		}

		s.gpa = calculateStudentGPA(s);																// ortalamayi hesaplamasi icin calculateStudentGPA() fonksiyonunu cagiriyoruz.
		printf("\n\nGPA = %.2f\n", s.gpa);															// ve ortalamayi bastiriyoruz
	}
	else
	{
		printf("Student is not registered in any courses.\n\n");									// eger kayit listesinin ilk elemaninin ders ismi "*"-e esitse bu hic ders yok demek.
	}
}

void displayCourseInfo(courses_t c)								// verilen dersin bilgilerini gosteren fonksiyon
{
	int i = 0;
	printf("\nCourse Name: %s\n", c.courseName);				// Dersin ismi
	printf("Course Code: %s\n", c.courseCode);					// Dersin kodu

	

	if (c.students[0].stNo)										// eger ilk ogrencinin numarasi NULL ise bu dizinin bos oldugunu gosterir.
	{
		printf("\nRegistered Students: \n\n");

		for(i = 0; c.students[i].stNo; i++)						// derse kayitli butun ogrencileri gostere bilmek icin ogrenci numarasi NULL olana kadar i-yi arttiriyoruz.
		{
			printf("Student Fullname: %s %s\n", c.students[i].studentName.name, c.students[i].studentName.surname);	// ogrenci isim ve soyimini bastiriyoruz
			printf("Student No: %s\n", c.students[i].stNo);		// ogrenci numarasini bastiriyoruz
		}

	}
	else
	{
		printf("\nNobody registered in this course.\n\n");		// dizi bossa hata mesaji gonderiyoruz
	}
}



void printClass(courses_t c)										// verilen dersin ogrencilerini yazdiran program
{
	int i = 0;

	printf("%s___________%s____\n\n", c.courseName, c.courseCode); 	// Ders ismi ve kodu

	// derse kayitli butun ogrencileri gostere bilmek icin ogrenci numarasi NULL olana kadar i-yi arttiriyoruz.
	for (i = 0; c.students[i].stNo != NULL; i++) printf("%s - %s %s\n", c.students[i].stNo, c.students[i].studentName.name, c.students[i].studentName.surname); 
	
	// dizi bossa hata mesaji gonderiyoruz
	if(i == 0) printf("\nNobody registered in this course.\n\n");
}

void printMenu() // statik Menuyu bastiran fonksiyon
{
	printf("__________________Menu__________________\n");
	printf("_                                      _\n");
	printf("_            1. Add Course             _\n");
	printf("_            2. Add Student            _\n");
	printf("_            3. Print Class            _\n");
	printf("_        4. Display Course Info        _\n");
	printf("_        5. Display Student Info       _\n");
	printf("_      6. Calculate Course Average     _\n");
	printf("_      7. Register for the Course      _\n");
	printf("_                0. Exit               _\n");
	printf("________________________________________\n");
	printf("\nChoose One: ");

}









courseReg_t registerCourse(student_t s, courses_t c)						// Kayit ekleme
{
	courseReg_t r;															// yeni Kayit yaratiyoruz
	
	strcpy(r.courseCode, c.courseCode);										// strcpy(hedef, kaynak); olarak calisir
	strcpy(r.courseName, c.courseName);										// burada ders isim ve kodunu kayida ekliyoruz

	while(1)
	{
		printf("\nEnter Grades\n \nMidterm: ");
		scanf("%lf", &r.grades.midterm);									// double degiskeni scanf ile almak
																			// icin "%lf" kullanilmalidir yoksa hatalar cika bilir
		printf("\nFinal: ");												// burada da vize, final, odev ve quiz cevaplari kullanicidan aliniyo
		scanf("%lf", &r.grades.final);

		printf("\nQuiz: ");
		scanf("%lf", &r.grades.quiz);

		printf("\nHomework: ");
		scanf("%lf", &r.grades.homework);

		if ((r.grades.midterm <= 100.00 && r.grades.midterm >= 0.00) &&		// burada kullanicinin girdigi sayilari kontrol ediyoruz 
			(r.grades.final <= 100.00 && r.grades.final >= 0.00) &&			// eger hepsi 100-den esit yada kucukse ve 0-dan esit yada
			(r.grades.quiz <= 100.00 && r.grades.quiz >= 0.00) &&			// buyukse donguden break ile cikiyoruz.
			(r.grades.homework <= 100.00 && r.grades.quiz >= 0.00))
			break;
		else printf("\n\nWrong Input!\n\n");								// degile hata mesaji verip dongunun basina gidiyoruz.
	}
	calculateStudentCourseGrade(&r);										// ve ogrencinin notu hesaplaniyor ve refansla deger gonderdigimizden
																			// fonksiyonun icinde degerler guncelleniyor.

	return r;
}


courses_t addCourse()							// Ders ekleme 
{
	courses_t c;								// yeni ders ekliyoruz

	printf("Course Name: ");
	scanf(" %s", c.courseName);					// Ders ismi aliyoruz kullanicidan

	printf("Course Code: ");
	scanf(" %s", c.courseCode);					// Ders kodu aliyoruz kullanicidan

	c.courseAverage = 0;						// baslangic olarakta 0-a esitliyoruz

	printf("\n\n___Course Added!___\n\n");		// Basari mesaji bastiriyoruz.
	return c;
}

student_t addStudent()																	// Ogrenci ekleme
{
	int i = 0;
	student_t s;																		// yeni ogrenci ekliyoruz

	s.stNo = malloc(STUDENTNUMBERLENGTH * (sizeof(*s.stNo)));							// stNo, studentName.name ve studentName.surname degiskenleri char array 
	s.studentName.name = malloc(NAMELENGTH * (sizeof(*s.studentName.name)));			// degilde char pointer verildiginden malloc fonksiyonu ile bellekte yer 
	s.studentName.surname = malloc(NAMELENGTH * (sizeof(*s.studentName.surname)));		// aciyoruz.

	for(i = 0; i < COURSESREGISTERED; i++) s.courses[i].courseName[0] = 42;				// butun ders isimlerin ilk harfini "*" yapiyoruz 
																						// diger fonksiyonlarda kolay bulunsun diye
	printf("\n\nStudent Name, Surname, No (etc. Serife Tan st1): ");
	scanf("%s %s %s", s.studentName.name, s.studentName.surname, s.stNo);				// Kullanicidan bilgileri aliyoruz
	printf("\n\n___Student Added!___\n\n");												// Basari mesaji bastiriyoruz.
	return s;
}





int main()
{
	courses_t courseClass[MAXCOURSESIZE];					// Dersleri tutmak icin kullaniyoruz
	student_t Students[MAXSTUDENTSIZE];						// ogrencileri tutmak icin kullaniyoruz
	int c = 0, i = 0, j = 0;								// c - islem secimini tutuyor; i - Ders sayini; j - ogrenci sayini
	system("cls");											// Konsolu temizlemek icin

	while (1) {												// c 0 olmadikca devam edecek
		printMenu();
		scanf("%d", &c);									// secimi yapiyoruz
		
		if (c == 0)											// eger 0 ise programi bitiriyoruz
		{
			break;
		} 
		else if (c == 1) 									// Ders ekleme
		{
			courseClass[i] = addCourse();
			i++;
		} 
		else if (c == 2) 									// ogrenci ekleme
		{
			Students[j] = addStudent();
			j++;
		} 
		else if (c == 3 || c == 4 || c == 6) 				// hepsi baslangicda girilen koda gore dersi bulup ardindan islem yaptigindan birlestirdim.
		{
			int s = 0;										// aranan index s-de tutulacak
			char *cr;										// aranan kod

			cr = malloc(COURSECODELENGTH * (sizeof(*cr)));	// bellekte yer ayiriyoruz

			printf("\nEnter Course Code: ");
			scanf(" %s", cr);								// kullanicidan aranacak kelimeyi aliyoruz

			s = findCourse(courseClass, cr);				// ve dersi ariyoruz...

			if(s == -1) printf("\n\nCourse with the code you entered was not found\n\n"); 	// s = -1 ise bu bulunamadi demek
			else 																			// aksi halde girilen secime gore fonksiyon cagiriyoruz
			{
				if (c == 3) printClass(courseClass[s]);
				else if(c == 4) displayCourseInfo(courseClass[s]);
				else if(c == 6) printf("Course Avarage: %.2f\n\n", calculateCourseAverage(courseClass[s]));
			}
			
		} 
		else if (c == 5) 
		{
			int s = 0;																			// aranan index s-de tutulacak
			char *st;																			// aranan numara

			st = malloc(STUDENTNUMBERLENGTH * (sizeof(*st)));									// bellekte yer ayiriyoruz

			printf("\nEnter Student No: ");
			scanf(" %s", st);																	// kullanicidan aranacak kelimeyi aliyoruz

			s = findStudent(Students, st);														// ve ogrenciyi ariyoruz...

			if(s == -1) printf("\n\nStudent with the number you entered was not found\n\n");	// s = -1 ise bu bulunamadi demek
			else displayStudentInfo(Students[s]);												// aksi halde ogrenci bilgilerini aliyoruz.

		} 
		else if (c == 7) 
		{
			int s = 0, c = 0;																// ogrencinin indexi s-de dersin indexi c-de tutulacak
			char *st, *cr;																	// aranan numarayi ve kodu tutacaklar

			cr = malloc(COURSECODELENGTH * (sizeof(*cr)));									// bellekte yer ayiriyoruz
			st = malloc(STUDENTNUMBERLENGTH * (sizeof(*st)));

			printf("\nEnter Student No: ");
			scanf(" %s", st);																// kullanicidan aranacak numarayi aliyoruz

			printf("\nEnter Course Code: ");
			scanf(" %s", cr);																// kullanicidan aranacak kodu aliyoruz

			c = findCourse(courseClass, cr);												// ve dersi ariyoruz...
			s = findStudent(Students, st);													// ve ogrenciyi ariyoruz...

			if(s == -1)																		// Ogrenci bulunamamissa true olacak
			{
				printf("\n\nStudent with the number you entered was not found\n\n");
			}
			else if (c == -1)																// Ders bulunamamissa true olacak
			{
				printf("\n\nCourse with the code you entered was not found\n\n");
			}
			else
			{
				int k = 0;

				while(courseClass[c].students[k].stNo != NULL) k++;							// derse yeni kaydi yapabilmek icin ogrenci numarasi NULL olana kadar k-yi arttiriyoruz.

				courseClass[c].students[k] = Students[s];									// ve kaydi yapiyoruz.

				k = 0;																		// baska degisken kullanmamak icin k-yi 0 yapip yeniden kullaniyoruz

				while(Students[s].courses[k].courseName[0] != 42) k++;						// Ogrencinin yeni kaydini eklemek icin ekli olan derslerin bi sonrasina bu dersi de ekliyoruz

				Students[s].courses[k] = registerCourse(Students[s], courseClass[c]);
				courseClass[c].courseAverage += Students[s].courses[k].numericGrade;		// ve ogrenci kayit ettikce notunu da courseAverage degiskenine ekliyoruz.
			}
		} 
		else
		{
			printf("\nWrong Input !!!\n\n");												// belirtilmeyen bir giris girdiginde hata verip yeniden soruyoruz.
		}
	}
	return 0;
}
