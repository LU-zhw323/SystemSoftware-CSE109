#include "linkedlist.h"

#include <stdlib.h> 
#include <stdio.h>
//#include "hashset.h"
#include<stdbool.h>

int main() {
	HashSet<int> hs(10);
  int a = 0x12ab345;
  int b = 0xfeed425;
  
  int c = 0xabcd38;
  int d = 0x1235698;
  int e = 0x2c374;
  int f = 0xa0f8982;
  int g = 0x053eba;
  int h = 0x61c2f5e;
  int i = 0xe0295f2;
  int j = 0x5e700eaa;
  int k = 0xe75bf1;
  int l = 0x6baa9bb;
  int m = 0x8b1390a;
  int n = 0x59dd1;
  int o = 0xfc32;
  int p = 0xa9d89d8;
  int q = 0x5b2c9e;
  int r = 0x2431e3;
  int s = 0x1910a;
  int t = 0x72;
  
  hs.insert(a);
	hs.insert(b);
  /*
  hs.insert(c);
  hs.insert(d);
  hs.insert(e);
  hs.insert(f);
  hs.insert(g);
  hs.insert(h);//
  hs.insert(i);
  hs.insert(j);
  hs.insert(k);
  hs.insert(l);
  hs.insert(m);
  hs.insert(n);
  hs.insert(o);
  hs.insert(p);
  hs.insert(q);
  hs.insert(r);
  hs.insert(s);
  hs.insert(t); // 14 of 20 buckets should be filled on this insert, causing another resize
  */
  printf("%d\n",hs.capacity());
  bool ss = hs.contains(a);
  printf("aaa:%x\n",ss);
  printf("T:%x\n",true);
  hs.print();
  //int x = hs->len();
  
  
	//hs->print();
  
}