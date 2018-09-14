#include <iostream>
#include <string>
#include <cstdlib>
#include <ctype.h>
#include <cstring>

//函数功能:实现表达式求值
//函数参数：
//exp 待求值的表达式（整数的四则混合运算表达式, 可以含有小括号）
//返回值：表达式的值

//后缀栈
struct suffix
{
	int a[20] = {0};
	int top;
};

//中缀栈
struct infix 
{
	char Operator[20] = "";
	int top;
};

//优先级比较
bool isNotLow(char a, char b)
{
    if ( a == '(' || b == '(') return false;
    if ((a == '+' || a == '-') && (b == '*' || b == '/' || b == '+' || b == '-'))
        return false;
    return true;
}


//中缀转后缀
int cale(std::string exp)
{
	int result;
	char ch;

	suffix s1;
	s1.top = 0;
	infix n1;
	n1.top = 0;

	std::string s;//后缀队列
	
	int i = 0;
	int len;
	int lenx = exp.length();
	while((!exp.empty()) && lenx+1 != i)
	{
		len = s.length();
		if(i < lenx)
		{
			ch = exp.at(i);
			if(isdigit(ch) != 0 )
				s.insert(len, 1, ch);
		}

		++i;

		if(isdigit(ch) == 0)
		{
			if(isNotLow(ch, n1.Operator[n1.top]) == true && n1.top != '(' && n1.Operator[n1.top])
                        {
				
                                n1.Operator[n1.top+1] = n1.Operator[n1.top];
                                n1.Operator[n1.top] = ch;
                        }
			if(isNotLow(ch, n1.Operator[n1.top]) == false && n1.top != '(' && n1.Operator[n1.top])
                        {
				s.insert(len, 1, n1.Operator[n1.top]);
				n1.Operator[n1.top] = ch;
                        }
			
			if(ch == '(')
			{
				
				n1.Operator[n1.top+1] = n1.Operator[n1.top];
				n1.Operator[n1.top] = ch;
			}
			int w = 0;
			while(ch == ')')
			{
				s.insert(len, 1, n1.Operator[n1.top+w]);
				if(n1.Operator[n1.top+w] == '(')
				{
					while(n1.Operator[n1.top+w+1])
						n1.Operator[n1.top+w] = n1.Operator[n1.top+w+1];
				}
				w++;
				
			}

			if(!n1.Operator[n1.top])
				n1.Operator[n1.top] = ch;

		}
		//std::cout<<n1.Operator<<n1.top<<std::endl;
		int x = 0;
		while(i == lenx+1)
		{
			
			s.insert(len, 1, n1.Operator[n1.top+x]);
			if(!n1.Operator[n1.top+x+1])
				break;
			len++;
			x++;
		}
		//std::cout << s << std::endl;
		//std::cout << n1.Operator[n1.top] << std::endl;
	}

	
	std::cout << s << std::endl;	

	//后缀实现个位的计算
	int l = 0;
	i = 0;
	len = s.length();
	int len1 = 0;
	while((!s.empty()) && len != i)	
	{
		l = 0;
		ch = s.at(i);
		++i;

		if(isdigit(ch) != 0)
		{
			while(s1.a[len1] != 0)
				len1++;

			//std::cout<<len1<<std::endl;
			while(len1 != 0)
			{
				s1.a[s1.top+len1] = s1.a[s1.top+len1-1];
				len1--;
			}

			s1.a[s1.top] = (ch)-48;
		}
		/*
		for(int h = 0; h < 5; h++)
			std::cout << s1.a[s1.top+h]<<' ';
			
		std::cout<<std::endl;
*/
		if(isdigit(ch) == 0)
		{
			switch(ch)
			{
				case '+':
				{
					s1.a[s1.top] = s1.a[s1.top+1] + s1.a[s1.top];
					s1.a[s1.top+1] = 0;
					while(s1.a[s1.top+2+l])
					{
						s1.a[s1.top+1+l] = s1.a[s1.top+2+l];
						++l;
					}
					break;
				}
				case '-':
                                {
                                        s1.a[s1.top] = s1.a[s1.top+1] - s1.a[s1.top];
					s1.a[s1.top+1] = 0;
                                        while(s1.a[s1.top+2+l])
                                        {
                                                s1.a[s1.top+1+l] = s1.a[s1.top+2+l];
                                                ++l;
                                        }
					break;
                                }
				case '*':
                                {
                                        s1.a[s1.top] = s1.a[s1.top+1] * s1.a[s1.top];
					s1.a[s1.top+1] = 0;
                                        while(s1.a[s1.top+2+l])
                                        {
                                                s1.a[s1.top+1+l] = s1.a[s1.top+2+l];
                                                ++l;
                                        }
					break;
                                }
				case '/':
                                {
                                        s1.a[s1.top] = s1.a[s1.top+1] / s1.a[s1.top];
					s1.a[s1.top+1] = 0;
                                        while(s1.a[s1.top+2+l])
                                        {
                                                s1.a[s1.top+1+l] = s1.a[s1.top+2+l];
                                                ++l;
                                        }
					break;
                                }
			}
			//std::cout << s1.a[s1.top] <<std::endl;
		}
/*
		for(int h = 0; h < 5; h++)
                        std::cout << s1.a[s1.top+h]<<' ';

                std::cout<<std::endl;
*/
		//std::cout << s1.a[s1.top]<< ' '<<s1.a[s1.top+1] <<std::endl;	
	}
	
	result = s1.a[s1.top];		
	return result;
}

int main()
{
	std::string exp;
	std::cin >> exp;
	std::cout<< cale(exp) << std::endl;
	//cale(exp);

	return 0;
}
