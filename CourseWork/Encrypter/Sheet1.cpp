#include "Header.h"

//To simply get the ASCII code, we'll have to just do a int(char) or int ('letter') like shown below.

class Func
{
	Common c;
public:
	int encrypt(int n , int steps)
	{
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
		return steps;
	}

	//Polymorphism -- 2.
	void to_file(string username)
	{
		c.encryption.open("encryption.txt", ios::app);
		// ios::out is write mode. we use \\ so as to not confuse with special characters in c++, as spl characters use \ (single slash).
		if (c.encryption.is_open())
		{
			c.encryption << username << "\t";
		}
		c.encryption.close();
	}
	void to_file(int* up, int n) // passing pointer to a function -- 2.
	{
		c.encryption.open("encryption.txt", ios::app);
		// ios::app is to append the file with it's existing content.

		if (c.encryption.is_open())
		{
			for (int i = 0; i < n; i++)
			{
				c.encryption << up[i];
			}
			c.encryption << "\n";
		}
		c.encryption.close();
	}
};


//Inheritance -- 2
class CreateUser : public Common
{
	Func f;

public:
	void user_entry(string username, string password)
	{
		//Writing username to file.
		f.to_file(username);


		int passsize = password.size(); // To determine the length of the password
		offset = 0;

		for (int i = 0; i < passsize; i++)
		{
			ascii = int(password[i]); // Conversion of char to it's ASCII
			steps = 0;
			n = ascii + offset;

			steps = f.encrypt(n, steps);

			user_pass_arr[i] = steps;
			offset = steps;
		}

		int m = 0, user_pass_arr_len = 0;
		while (user_pass_arr[m] != '\0')
		{
			m++;
		}

		user_pass_arr_len = m;
		m = 0;

		int* up = user_pass_arr; //Using pointers to store an array

		//Writing password to a file.
		f.to_file(up, user_pass_arr_len); //Passing in a pointer to a function.
	}
	
};


int main()
{
	Common c;
	CreateUser cu;
	Func f;

	c.clrscr();
	char exit, main_menu_choice;

	do
	{
		c.clrscr();
		cout << "\t\t\t**********!!! WELCOME !!!**********\n\n\t\t\t1.Create User Record\n\t\t\t2.Validate User Credentials\n\t\t\t3.Generate Random Password File\n\t\t\t4.Exit :: ";
		cin >> main_menu_choice;

		try
		{
			if (main_menu_choice != '1' && main_menu_choice != '2' && main_menu_choice != '3' && main_menu_choice != '4')
			{
				throw(main_menu_choice);
			}
			else
			{
				switch (main_menu_choice)
				{
				case '1':
				{
					//Using auto keyword and lambda function.
					auto lam = []()
					{
						cout << "Enter Username:\n";
					};

					lam();

					cin.ignore(); //If this is not included, the cin would take the previous \n as input for getline as \n indicates new line. So we ignore that input and take new.
					getline(cin, c.username); //Takes input with whiteSpaces.

					cout << "Enter Password:\n";
					cin.ignore();
					getline(cin, c.password);

					cout << "\n";

					cu.user_entry(c.username, c.password);

				} break;

				case '2':
				{

					int retries = 3;
					bool fetch = false;
					string line;
					c.encryption.open("encryption.txt", ios::in); // ios::in is for reading file.

					cout << "Enter Username:\n";

					cin.ignore();
					getline(cin, c.username);

					//Exception Handling for catching file system exception -- 6 + 2 = 8
					try
					{
						if (c.encryption.is_open())
						{
							cout << "\n\t\tFile Exist !!!\n\n";
						}
						else
						{
							throw (0);
						}
					}
					catch (int c)
					{
						cout << "\n\t\tFile Doesn't Exist !!!\n\n";
						break;
					}


					if (c.encryption.is_open())
					{
						//To fetch the line from file whose username matches with user input.
						while (getline(c.encryption, line))
						{

							int i = 0;
							string auth;
							while (line[i] != '\t')
							{
								auth = auth + line[i];
								i++;
							}

							if (auth == c.username)
							{
								c.pos1 = i + 1;
								cout << "\n\t\tUsername Matched !!!\n";
								fetch = true;

								do
								{

									cout << "Enter Password:\n";
									cin.ignore();
									getline(cin, c.password);

									cout << "\n";

									//To determine the length of the password
									int passsize = c.password.size();

									c.offset = 0;
									c.user_pass_str = "";

									for (int i = 0; i < passsize; i++)
									{
										c.ascii = int(c.password[i]); //Conversion of char to it's ASCII
										c.steps = 0;
										c.n = c.ascii + c.offset;

										c.steps = f.encrypt(c.n, c.steps);

										c.user_pass_str += to_string(c.steps);
										c.offset = c.steps;
									}

									c.pos1 = 0;
									c.pos2 = 0;

									while (line[c.pos1] != '\t')
									{
										c.pos1++;
									}

									c.pos1++;

									c.encryp_pass_str = "";
									//To store encrypt values from file to a vector.
									do
									{
										c.encryp_pass_str += line[c.pos1];
										c.pos2++;
										c.pos1++;

									} while (c.pos1 < line.length());

									//int m = 0;
									int compok = 0;
									int compfa = 0;

									cout << "user_pass_str :: " << c.user_pass_str;
									cout << "encryp_pass_str ::" << c.encryp_pass_str;

									if (c.user_pass_str == c.encryp_pass_str)
									{
										compok++;
										//m++;
									}
									else
									{
										compfa++;
										//m++;
									}

									if (compok == 1 && compfa == 0)
									{
										cout << "\n\t\tAuthentication Successful !!!\n\t\tWelcome " << c.username << " !!!\n\n";
										retries = 0;
									}
									else if (compfa != 0)
									{
										cout << "\n\t\tAuthentication Failed !!!\n\t\tTry Again\n\n";
										retries--;
										c.pos2 = 0;
										c.pos1 = 0;
										cout << "\n\t\tRetries Left :: " << retries << " !!!\n\n";

									}

								} while (retries != 0);

							}
							else
							{
								fetch = false;
								break;
							}

						}

						if (fetch == false)
						{
							char yn;
							cout << "\n\t\tUsername Not Found !!!\n\t\tYou Might Want To Create A New User Record !!!\n\n";
							cout << "\n\t\tDo You Wish To Coninue Creating A New User Record ? (y/n)\n";
							cin >> yn;
							if (yn == 'y' || yn == 'Y')
							{
								break;
							}
							else if (yn == 'n' || yn == 'N')
							{
								break;
							}
						}

					}

					c.encryption.close();

				} break;

				case '3':
				{
					char yn;
					char char_arr[26];
					vector<char>char_vec;
					char rand_arr[10];
					int pass_len = 0;
					fstream test;

					cout << "\n\t\tPress 'y' or 'Y' to generate 20000 passwordtest file :: Test.txt :: ";
					cin >> yn;

					if (yn == 'y' || yn == 'Y')
					{
						test.open("Test.txt", ios::app);

						if (test.is_open())
						{
							int no = 0;

							srand((unsigned)time(NULL)); //For generating random values for each iteration of rand().

							for (char i = 'a'; i <= 'z'; i++)
							{
								char_arr[no] = i;
								no++;
							}

							//To generate 1st 10000 random passwords.
							for (int i = 0; i < 10000; i = i + 100)
							{
								pass_len++;

								for (int j = 0; j < 100; j++)
								{

									for (int k = 0; k < 10; k++)
									{
										rand_arr[k] = char_arr[rand() % no];
									}

									string a;

									for (int l = 0; l < pass_len; l++)
									{
										a = a + rand_arr[rand() % sizeof(rand_arr)];
									}

									string b;
									c.offset = 0;

									for (int m = 0; m < a.length(); m++)
									{
										c.ascii = int(a[m]);  //Conversion of char to it's ASCII
										c.steps = 0;
										c.n = c.ascii + c.offset;

										c.steps = f.encrypt(c.n, c.steps);

										b += to_string(c.steps);
										c.offset = c.steps;
									}
									test << b << "\n";
								}
							}

							int no1 = 0;
							pass_len = 0;

							//To get printable and extended ASCII characters.
							for (unsigned int i = 32; i < 255; i++)
							{
								char_vec.push_back(char(i));
								no1++;
							}

							srand((unsigned)time(NULL)); //For generating random values for each iteration of rand().


							//To generate 2nd 10000 random passwords.
							for (int i = 0; i < 10000; i = i + 100)
							{
								pass_len++;

								for (int j = 0; j < 100; j++)
								{

									vector<char>a;
									vector<char>b;
									string temp;
									bool break0 = false;

									for (int l = 0; l < pass_len; l++)
									{
										do
										{
											break0 = false;
											a.push_back(char_vec[rand() % char_vec.size()]);

											if (pass_len == 1)
											{
												temp = temp + char_vec[rand() % char_vec.size()];
											}
											else if (pass_len != 1 && pass_len != 0)
											{
												while (b.size() != a.size())
												{
													if (b.empty() == true)
													{
														for (int j = 0; j < a.size(); j++)
														{
															b.push_back(a[j]);
															temp = temp + b[b.size() - 1];
														}
													}
													else
													{
														int match = 0;
														int unmatch = 0;
														int l_pos_a = a.size() - 1; //To get the last values position in a vector.

														//Taking last element of a to compare with the elemets in another array or vector or string.
														for (int p = 0; p < temp.length(); p++)
														{
															if (temp[p] == a[l_pos_a])
															{
																match++;
															}
															else
															{
																unmatch++;
															}
														}

														if (match != 0)
														{
															a.pop_back();
															break0 = true;
															break;
														}
														else if (unmatch != 0 && match == 0)
														{
															b.push_back(a[l_pos_a]);
															temp = temp + b[b.size() - 1];
														}
													}
												}
											}
										} while (break0 == true);
									}

									string temp2;
									c.offset = 0;
									int t = 0;

									if (temp.length() != 0)
									{
										for (int m = 0; m < temp.length(); m++)
										{
											c.ascii = int(unsigned char(temp[m])); //Conversion of char to it's ASCII
											c.steps = 0;
											t = c.ascii + c.offset;

											c.steps = f.encrypt(t, c.steps);

											temp2 += to_string(c.steps);
											c.offset = c.steps;
										}
									}

									test << temp2 << "\n";
								}

								cout << "\n\ni :: " << i;
							}
						}

						test.close();
					}
					else
					{
						break;
					}
				} break;

				case '4':
				{
					char d;
					cout << "\n\n\t\tDo you wish to exit? y/n :: ";
					cin >> d;

					if (d == 'y' || d == 'Y')
					{
						break;
					}
					else
					{

					}
				}

				default:
				{
					cout << "\n\n\t\tPlease Enter a valid input !!!";
				} break;
				}
			}
			
		}
		catch (char wrong_input)
		{
			cout << "\n\n\t\t" << wrong_input << " is not a valid input !!!";
			cout << "\n\n\t\tPlease Enter a valid input !!!";
		}

		cout << "\n\n\t\tDo you wish to continue? y/n :: ";
		cin >> exit;

	} while (exit == 'y' || exit == 'Y');
}