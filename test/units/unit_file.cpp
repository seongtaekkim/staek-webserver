
// // std::string listing(File file)
// // {
// // 	const std::string &directory = file.path();

// // 	std::string out = ""
// // 			"<html>\n"
// // 			"	<head>\n"
// // 			"		<title>Listing of " + directory + "</title>\n"
// // 			"	</head>\n"
// // 			"	<body>\n";

// // 	std::list<File> files = file.list();
// // 	for (std::list<File>::iterator it = files.begin(); it != files.end(); it++)
// // 	{
// // 		std::string name(it->name());

// // 		if (it->isDir())
// // 			name += '/';

// // 		std::string path(file.path());
// // 		if (path.empty()) // TODO Need rework!
// // 			path += '/';


// // 		path += name;

// // 		out += std::string("<a href=\"") + path + "\">" + name + "</a><br>\n";
// // 	}

// // 	out += ""
// // 			"	</body>\n"
// // 			"</html>\n";

// // 	return (out);
// // }


// #include <bitset>
// int main(void) {
// 	File f("FileDescriptor.cpp");
// 	File f2("FileDescriptor.hpp");
// 	std::cout <<  std::bitset<16>(f.stat().st_mode) << std::endl;
// 	std::cout << f2.stat().st_mode << std::endl;
// 	std::cout << std::bitset<8>(S_ISREG(f2.stat().st_mode)) << std::endl;
// 	std::cout << std::bitset<8>(S_ISDIR(f2.stat().st_mode)) << std::endl;
// 	std::cout << f2.isExecutable() << std::endl;
// 	std::cout << f2.size() << std::endl;
// 	// File n("./new/newfile");
// 	// std::cout << n.create() << std::endl;
// 	// n.remove();
// 	// File f3("./new/");
// 	// std::list<File> l = f3.list();
// 	// std::list<File>::iterator bit = l.begin();
	
// 	// for (std::list<File>::iterator i = bit ; i != l.end() ; i++) {
// 	// 	 std::cout << i->path() << std::endl;
// 	// }
// 	// std::cout << listing(f3) << std::endl;

// 	// File f4("new/test1");
// 	File f4("./new/test1");
// 	std::cout << f4.getExtension() << std::endl;
// 	std::cout << f4.name() << std::endl;
// 	std::cout << f4.indexOfSeparator() << std::endl;
// 	std::cout << (f4.indexOfExtension() == std::string::npos) << std::endl;
// 	std::cout << (std::string::size_type(-1) == std::string::npos) << std::endl;
	
// }