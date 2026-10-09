// Author: KRa Tos (Константин) | Project: Unesennye Music System v1.3.0
// Do not remove this header. Unauthorized redistribution is prohibited.

class UnesennyeLogger
{
	static void EnsureDir()
	{
		if (!FileExist(UnesennyeConstants.PROFILE_DIR))
			MakeDirectory(UnesennyeConstants.PROFILE_DIR);
	}

	static void Log(string msg)
	{
		Print("[Unesennye] " + msg);

		if (UnesennyeConfig.Get() && !UnesennyeConfig.Get().FileLogEnabled)
			return;

		EnsureDir();
		FileHandle f = OpenFile(UnesennyeConstants.LOG_FILE, FileMode.APPEND);
		if (f == 0)
			return;

		int y, m, d, hh, mm, ss;
		GetYearMonthDay(y, m, d);
		GetHourMinuteSecond(hh, mm, ss);
		string ts = y.ToString() + "-" + m.ToStringLen(2) + "-" + d.ToStringLen(2) + " " + hh.ToStringLen(2) + ":" + mm.ToStringLen(2) + ":" + ss.ToStringLen(2);
		FPrintln(f, ts + " | " + msg);
		CloseFile(f);
	}
};
