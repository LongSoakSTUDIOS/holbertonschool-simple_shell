int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	long int result = 0;
    int isnumber = 0;

	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;


	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		result = (result * 10) + (s[i] - '0');
        isnumber = 1;
		i++;
	}

    if (isnumber == 0)
    {
        return (-1);
    }
	return ((int)(result * sign));
}