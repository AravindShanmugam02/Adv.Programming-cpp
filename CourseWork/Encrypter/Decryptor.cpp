#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

class decry
{
public:
	void main()
	{
		vector<char>alpha;
		vector<char>value;
		string decry, temp;
		int decry_len, match = 0, iteration = 0;
		string decrypt;
		int alp_size = 0, inp_size = 0, offset = 0, steps = 0, n = 0, ascii = 0;
		string input, line;
		fstream file;
		int num_pass = 0, cat_pass[200], cat = 0, tot_pass = 0, len = 0, l = 0, tim_per_ite = 0, tim_per_cat[200], tot_time = 0;


		file.open("Test.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				//cout << "Checkpoint 1";
				auto start = high_resolution_clock::now();

				l++;
				cout << "\nIteration :: " << l;
				alpha.clear();

				//cout << "Checkpoint 2";
				if (l < 10001)
				{
					for (char i = 'a'; i <= 'z'; i++)
					{
						alpha.push_back(i);
					}
				}
				else
				{
					for (unsigned int i = 32; i < 255; i++)
					{
						alpha.push_back(unsigned char(i));
					}
				}
				//cout << "Checkpoint 3";
				alp_size = alpha.size();

				if (file.is_open())
				{
					//cout << "Checkpoint 5";
					input = line;
					inp_size = input.length();
					int inp_indi = 0;

					do
					{
						//cout << "Checkpoint 6";
						int i = 0;

						while (i < alp_size)
						{
							//cout << "Checkpoint 7";
							ascii = int(alpha[i]);
							steps = 0;
							n = ascii + offset;

							while (n != 1)
							{
								if (n % 2 == 0)
								{
									// n is even;
									n = n / 2;
									steps++;
								}
								else if (n % 2 != 0)
								{
									// n is odd;
									n = (3 * n) + 1;
									steps++;
								}
							}
							//cout << "Checkpoint 8";
							decry = decry + to_string(steps);
							decry_len = decry.length();
							match = 0; len = 0;

							len = len + inp_indi;
							//cout << "Checkpoint 9";
							if (len != 0)
							{
								if (decry.length() < (input.length() - len))
								{
									for (int j = 0; j < decry_len; j++)
									{
										temp = temp + input[len];
										//cout << "reach 1";
										len++;
									}
								}
							}
							else if (len == 0)
							{
								if (decry.length() <= input.length())
								{
									for (int j = 0; j < decry_len; j++)
									{
										temp = temp + input[len];
										//cout << "reach 1";
										len++;
									}
								}
							}


							//cout << "Checkpoint 10";
							if (decry == temp)
							{
								offset = steps;
								inp_indi = inp_indi + (len - 1);
								match = match + inp_indi;
								value.push_back(alpha[i]);
								temp = "";
								decry = "";
								i++;
								break;
							}
							else
							{
								steps = 0;

								if (value.empty() == true)
								{
									inp_indi = 0;
									offset = 0;
								}
								temp = "";
								decry = "";
							}
							//cout << "Checkpoint 11";
							i++;

						}
						//cout << "Checkpoint 12";
						if (i == alp_size && match != inp_size)
						{
							num_pass++;
							inp_indi = 0;
							offset = 0;
							steps = 0;
							break;
						}
					} while (match != inp_size);
					//cout << "Checkpoint 13";

					if (match == inp_size)
					{
						string answer;

						for (int i = 0; i < value.size(); i++)
						{
							answer = answer + value[i];
						}
						cout << "\n\t\tAnswer :: \n\t\t" << answer;
						inp_indi = 0;
						offset = 0;
						steps = 0;
						value.clear();

					}
					else
					{
						cout << "\n\t\tPasswords Uncracked !!!";
						inp_indi = 0;
						offset = 0;
						steps = 0;
					}
				}
				else
				{
					cout << "\n\t\tFile doesn't exist!!!";
					break;
				}
				//cout << "Checkpoint 14";
				auto stop = high_resolution_clock::now();

				auto duration = duration_cast<seconds>(stop - start);

				tim_per_ite = tim_per_ite + unsigned int(duration.count());

				//if (file.is_open() == false)
				//{
				//	file.open("Test.txt", ios::in);
				//}

				if (l % 100 == 0)
				{
					cat_pass[cat] = num_pass;
					tot_pass += num_pass;
					num_pass = 0;

					//Time
					tim_per_cat[cat] = tim_per_ite;
					tot_time += tim_per_ite;
					tim_per_ite = 0;
					cat++;
				}
			}
		}

		//cout << "Checkpoint 15";

		if (file.is_open())
		{
			//cout << "Checkpoint 38";
			cout << "\n\t\tTotal Number of Passords Cracked :: " << 20000 - tot_pass;

			//cout << "\n\t\t[FIRST 10000]Number of Passords Uncracked in each category :: ";

			//for (int i = 0; i < 100; i++)
				//cout << "\nCategory :: 1 - 100000 :: " << i << " :: " << cat_pass[i];

			//cout << "\n\t\t[SECOND 10000]Number of Passords Uncracked in each category :: ";

			//for (int i = 100; i < 200; i++)
				//cout << "\nCategory :: 100001 - 20000 :: " << i << " :: " << cat_pass[i];

			//Percentage
			cout << "\n\t\t[ToTal 20000]Percentage of passwords cracked in each category :: ";

			for (int i = 0; i < 200; i++)
				cout << "\nCategory :: 1 - 20000 :: " << i << " :: " << ((100 - cat_pass[i]) / 100) * 100 << "%";

			//Time
			cout << "\n\t\t[FIRST 10000]Average Time Taken to Crack Passwords in each category :: ";

			for (int i = 0; i < 100; i++)
				cout << "\nCategory :: 1 - 100000 :: " << i << " :: " << (tim_per_cat[i] / 100);

			cout << "\n\t\t[SECOND 10000]Average Time Taken to Crack Passwords in each category :: ";

			for (int i = 100; i < 200; i++)
				cout << "\nCategory :: 100001 - 20000 :: " << i << " :: " << (tim_per_cat[i] / 100);

			file.close();
		}

};