// Your project's error handler (you can put it anywhere you want, in a different file, even):
function void ACSUtilsErrorHandler(int type, int message)
{
	Log(s:"error: ", s:message);
	printbold(s:"error: ", s:message);
}
