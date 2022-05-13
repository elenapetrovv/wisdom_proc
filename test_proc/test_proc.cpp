#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Елена\Documents\GitHub\wisdom_proc\wisdom_proc.cpp"
#include "C:\Users\Елена\Documents\GitHub\wisdom_proc\source.cpp"
#include "C:\Users\Елена\Documents\GitHub\wisdom_proc\header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testproc
{
	TEST_CLASS(testproc)
	{
	public:
		TEST_METHOD(TestCountSymbols)
		{
			wisdom wd;
			wd.text = "1!!!.";
			int res = CountSymbols(wd);
			int exp = 4;
			Assert::AreEqual(exp, res);
		}
		TEST_METHOD(TestCompare)
		{
			wisdom wd1, wd2;
			wd1.text = "1,2.";
			wd2.text = "1!";
			Node* n1, * n2;
			n1 = new Node;
			n2 = new Node;
			n1->thought = &wd1;
			n2->thought = &wd2;
			bool res = Compare(n1, n2);
			bool exp = false;
			Assert::AreEqual(exp, res);
		}
		TEST_METHOD(TestIn)
		{
			ifstream ifst("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/inTest.txt");

			aphorism_wisdom* a = new aphorism_wisdom;
			saying_wisdom* s = new saying_wisdom;
			riddle_wisdom* r = new riddle_wisdom;

			In(ifst, *a);
			In(ifst, *s);
			In(ifst, *r);

			Assert::AreEqual(string("testAphorism"), a->author);
			Assert::AreEqual(string("testSaying"), s->country);
			Assert::AreEqual(string("testRiddle"), r->answer);
		}
		TEST_METHOD(TestInput)
		{
			ifstream ifst;
			ifst.open("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/inputTest.txt");
			container c;

			bool res = true;
			bool exp = true;

			//Assert::AreEqual(res, exp);
			InCont(ifst, &c);

			container c1;
			Node* n1, * n2, * n3;

			n1 = new Node;
			n1->thought = new wisdom;
			n1->thought->text = "testAphorism";
			n1->thought->rate = 1;
			n1->thought->key = wisdom::type::aphorism;
			aphorism_wisdom* a;
			a = new aphorism_wisdom;
			a->author = "author";
			n1->thought->a = *a;

			n2 = new Node;
			n2->thought = new wisdom;
			n2->thought->text = "testSaying";
			n2->thought->rate = 2;
			n2->thought->key = wisdom::type::saying;
			saying_wisdom* s;
			s = new saying_wisdom;
			s->country = "country";
			n2->thought->s = *s;

			n3 = new Node;
			n3->thought = new wisdom;
			n3->thought->text = "testRiddle";
			n3->thought->rate = 3;
			n3->thought->key = wisdom::type::riddle;
			riddle_wisdom* r;
			r = new riddle_wisdom;
			r->answer = "answer";
			n3->thought->r = *r;

			c1.head = n1;
			c1.head->next = n2;
			c1.head->next->next = n3;
			c1.head->prev = c1.head->next->next;
			c1.head->next->prev = c1.head;
			c1.head->next->next->prev = c1.head->next;
			c1.size = 3;

			Assert::AreEqual(int(c1.size), int(c.size));

			c.current = c.head;
			c1.current = c1.head;
			while (c.current->next != c.head)
			{

				Assert::AreEqual(string(c1.current->thought->text), string(c.current->thought->text));
				Assert::AreEqual(int(c1.current->thought->rate), int(c.current->thought->rate));

				if (c1.current->thought->key == wisdom::type::aphorism)
				{
					Assert::AreEqual(string((c1.current->thought->a.author)), string((c.current->thought->a.author)));
				}
				if (c1.current->thought->key == wisdom::type::saying)
				{
					Assert::AreEqual(string((c1.current->thought->s.country)), string((c.current->thought->s.country)));
				}
				if (c1.current->thought->key == wisdom::type::riddle)
				{
					Assert::AreEqual(string((c1.current->thought->r.answer)), string((c.current->thought->r.answer)));
				}
				c.current = c.current->next;
				c1.current = c1.current->next;
			}
		}
		TEST_METHOD(TestOut)
		{
			ofstream ofst("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/outTest.txt");
			bool exp = true;
			bool res = false;

			aphorism_wisdom* a = new aphorism_wisdom;
			a->author = "author";

			saying_wisdom* b = new saying_wisdom;
			b->country = "country";

			riddle_wisdom* r = new riddle_wisdom;
			r->answer = "answer";

			Out(ofst, *a);
			Out(ofst, *b);
			Out(ofst, *r);

			ifstream ifst1("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/outTest.txt");
			ifstream ifst2("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/expOutTest.txt");
			char c1, c2;
			while (ifst1.get(c1) && ifst2.get(c2))
			{
				Assert::AreEqual(c1, c2);
			}
		}
		TEST_METHOD(TestOutput)
		{
			ofstream ofst;
			ofst.open("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/outputTest.txt");
			container c;

			bool res = true;
			bool exp = true;

			Node* n1, * n2, * n3;

			n1 = new Node;
			n1->thought = new wisdom;
			n1->thought->text = "testAphorism";
			n1->thought->rate = 1;
			n1->thought->key = wisdom::type::aphorism;
			aphorism_wisdom* a;
			a = new aphorism_wisdom;
			a->author = "author";
			n1->thought->a = *a;

			n2 = new Node;
			n2->thought = new wisdom;
			n2->thought->text = "testSaying";
			n2->thought->rate = 2;
			n2->thought->key = wisdom::type::saying;
			saying_wisdom* s;
			s = new saying_wisdom;
			s->country = "country";
			n2->thought->s = *s;

			n3 = new Node;
			n3->thought = new wisdom;
			n3->thought->text = "testRiddle";
			n3->thought->rate = 3;
			n3->thought->key = wisdom::type::riddle;
			riddle_wisdom* r;
			r = new riddle_wisdom;
			r->answer = "answer";
			n3->thought->r = *r;

			c.head = n1;
			c.head->next = n2;
			c.head->next->next = n3;
			c.head->prev = c.head->next->next;
			c.head->next->prev = c.head;
			c.head->next->next->prev = c.head->next;
			c.head->next->next->next = c.head;
			c.size = 3;
			c.current = c.head;

			OutCont(ofst, &c);

			ifstream ifst1("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/outputTest.txt");
			ifstream ifst2("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/expOutputTest.txt");
			char c1, c2;
			while (ifst1.get(c1) && ifst2.get(c2))
			{
				Assert::AreEqual(c1, c2);
			}
		}
		TEST_METHOD(TestClear)
		{
			container c;

			bool res = true;
			bool exp = true;

			Node* n1, * n2, * n3;

			n1 = new Node;
			n1->thought = new wisdom;
			n1->thought->text = "testAphorism";
			n1->thought->rate = 1;
			n1->thought->key = wisdom::type::aphorism;
			aphorism_wisdom* a;
			a = new aphorism_wisdom;
			a->author = "author";
			n1->thought->a = *a;

			n2 = new Node;
			n2->thought = new wisdom;
			n2->thought->text = "testSaying";
			n2->thought->rate = 2;
			n2->thought->key = wisdom::type::saying;
			saying_wisdom* s;
			s = new saying_wisdom;
			s->country = "country";
			n2->thought->s = *s;

			n3 = new Node;
			n3->thought = new wisdom;
			n3->thought->text = "testRiddle";
			n3->thought->rate = 3;
			n3->thought->key = wisdom::type::riddle;
			riddle_wisdom* r;
			r = new riddle_wisdom;
			r->answer = "answer";
			n3->thought->r = *r;

			c.head = n1;
			c.head->next = n2;
			c.head->next->next = n3;
			c.head->prev = c.head->next->next;
			c.head->next->prev = c.head;
			c.head->next->next->prev = c.head->next;
			c.head->next->next->next = c.head;
			c.size = 3;
			c.current = c.head;


			Clear(&c);
			Assert::AreEqual(true, c.head == NULL);
			Assert::AreEqual(true, c.current == NULL);
			Assert::AreEqual(true, c.size == 0);
		}
		TEST_METHOD(TestSort)
		{
			container c1;
			container c;

			ifstream ifst("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/sortTest.txt");

			bool res = true;
			bool exp = true;

			Node* n1, * n2, * n3;

			n1 = new Node;
			n1->thought = new wisdom;
			n1->thought->text = "testAphorism!";
			n1->thought->rate = 1;
			n1->thought->key = wisdom::type::aphorism;
			aphorism_wisdom* a;
			a = new aphorism_wisdom;
			a->author = "author";
			n1->thought->a = *a;

			n2 = new Node;
			n2->thought = new wisdom;
			n2->thought->text = "testSaying!!";
			n2->thought->rate = 2;
			n2->thought->key = wisdom::type::saying;
			saying_wisdom* s;
			s = new saying_wisdom;
			s->country = "country";
			n2->thought->s = *s;

			n3 = new Node;
			n3->thought = new wisdom;
			n3->thought->text = "testRiddle!!!";
			n3->thought->rate = 3;
			n3->thought->key = wisdom::type::riddle;
			riddle_wisdom* r;
			r = new riddle_wisdom;
			r->answer = "answer";
			n3->thought->r = *r;

			c1.head = n1;
			c1.head->next = n2;
			c1.head->next->next = n3;
			c1.head->prev = c1.head->next->next;
			c1.head->next->prev = c1.head;
			c1.head->next->next->prev = c1.head->next;
			c1.head->next->next->next = c1.head;
			c1.size = 3;
			c1.current = c1.head;

			InCont(ifst, &c);
			Sort(c1);

			Assert::AreEqual(int(c1.size), int(c.size));

			c.current = c.head;
			c1.current = c1.head;
			while (c.current->next != c.head)
			{

				Assert::AreEqual(string(c1.current->thought->text), string(c.current->thought->text));
				Assert::AreEqual(int(c1.current->thought->rate), int(c.current->thought->rate));

				if (c1.current->thought->key == wisdom::type::aphorism)
				{
					Assert::AreEqual(string((c1.current->thought->a.author)), string((c.current->thought->a.author)));
				}
				if (c1.current->thought->key == wisdom::type::saying)
				{
					Assert::AreEqual(string((c1.current->thought->s.country)), string((c.current->thought->s.country)));
				}
				if (c1.current->thought->key == wisdom::type::riddle)
				{
					Assert::AreEqual(string((c1.current->thought->r.answer)), string((c.current->thought->r.answer)));
				}
				c.current = c.current->next;
				c1.current = c1.current->next;
			}
		}
		TEST_METHOD(TestOutAphorisms)
		{
			ofstream ofst;
			ofst.open("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/outAphorisms.txt");
			container c;

			bool res = true;
			bool exp = true;

			Node* n1, * n2, * n3;

			n1 = new Node;
			n1->thought = new wisdom;
			n1->thought->text = "testAphorism!";
			n1->thought->rate = 1;
			n1->thought->key = wisdom::type::aphorism;
			aphorism_wisdom* a;
			a = new aphorism_wisdom;
			a->author = "author";
			n1->thought->a = *a;

			n2 = new Node;
			n2->thought = new wisdom;
			n2->thought->text = "testSaying!!";
			n2->thought->rate = 2;
			n2->thought->key = wisdom::type::saying;
			saying_wisdom* s;
			s = new saying_wisdom;
			s->country = "country";
			n2->thought->s = *s;

			n3 = new Node;
			n3->thought = new wisdom;
			n3->thought->text = "testRiddle!!!";
			n3->thought->rate = 3;
			n3->thought->key = wisdom::type::riddle;
			riddle_wisdom* r;
			r = new riddle_wisdom;
			r->answer = "answer";
			n3->thought->r = *r;

			c.head = n1;
			c.head->next = n2;
			c.head->next->next = n3;
			c.head->prev = c.head->next->next;
			c.head->next->prev = c.head;
			c.head->next->next->prev = c.head->next;
			c.head->next->next->next = c.head;
			c.size = 3;
			c.current = c.head;

			OutAphorisms(ofst, &c);

			ifstream ifst1("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/outAphorisms.txt");
			ifstream ifst2("C:/Users/Елена/Documents/GitHub/wisdom_proc/test_proc/expOutAphorisms.txt");
			char c1, c2;
			while (ifst1.get(c1) && ifst2.get(c2))
			{
				Assert::AreEqual(c1, c2);
			}
		}
	};
}
