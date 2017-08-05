/* mtalk.cpp
Modem communication utility
[2017/03/10]
*/

#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include <pthread.h>

#define BAUDRATE B115200 
#define MODEMDEVICE "/dev/ttyACM2"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

using namespace std;

void *modem_reader(void *argument);

class NMEAName {
	char str[40];
public:
	NMEAName() { strcpy(str, ""); }
	NMEAName(char *s) { strcpy(str, s); }
	char *get() { return str; }
};

// Must define less than relative to name objects.
bool operator<(NMEAName a, NMEAName b)
{
	return strcmp(a.get(), b.get()) < 0;
}

class NMEAInfo {
public:
	char str[80];
	int count;
public:
	NMEAInfo() { 
		strcmp(str, "");
		count = 0;
	}
	NMEAInfo(char *s) {
		strcpy(str, s);
		count = 0;
	}
	NMEAInfo operator=(NMEAInfo info2) {
		strcpy(str, info2.str);
		return *this;
	}
	NMEAInfo operator+=(NMEAInfo info2) {
		strcpy(str, info2.str);
		count ++;
		return *this;
	}
	
	char *get_str() { return str; }
	int get_count() { return count; }
	int update(NMEAInfo ainfo) {
		strcpy(str, ainfo.get_str());
		count++;
		return count;
	}
	void show(string &astr) {
		char buf[100];
		sprintf(buf, "[%d]:%s\n", count, str);
		astr = buf;
	}
};

std::ostream &operator<<(std::ostream &os, NMEAInfo const &m) { 
	return os << "[" << m.count << "]:" << m.str;
}
	
map <NMEAName, NMEAInfo> nmea;

int handle_nmea_message(char *msg) {
	if (msg[0] != '$') {
		return 1;
	}
	
	NMEAInfo info(msg);
	char *pname = strtok(msg, ",");
	if (!pname) {
		return 2;
	}

	NMEAName name(pname);
	map <NMEAName, NMEAInfo>::iterator p;
  
	p = nmea.find(NMEAName(pname));
	if(p != nmea.end()) {
		NMEAInfo & ainfo = p->second;

		ainfo += info;
		cout << "<" <<  p->second.get_count() << ">" << p->second.get_str();
	}
	else {
		cout << "+<" << info.get_str() << endl;
		nmea.insert(std::make_pair(name, info));
	}

	return 0;
}

void show_nmea() {
    std::map <NMEAName, NMEAInfo>::iterator it = nmea.begin();
    printf("%s+:\n", __FUNCTION__);
    while(it != nmea.end())
    {
	NMEAName name;
	NMEAInfo & info = it->second;
	name = it->first;
        std::cout << info <<std::endl;
        it++;
    }
}
	
class ModemPort {
public:
	ModemPort () {
		printf("%s:\n", __FUNCTION__);
		fd = 0;
//		t1 = NULL;
		strcpy(comport, MODEMDEVICE);
		comspeed = BAUDRATE;
		
	}
	
	~ModemPort () {
		printf("%s:\n", __FUNCTION__);
//		if (t1) {
//			t1->detach();
//		}
		pthread_detach(thread_workder);
		closeport();
	}

#define CFGTAG_COMPORT "comport="
#define CFGTAG_COMSPEED "comspeed="
#define CFGTAG_ATCOMMAND "AT"

	void loadconfig(void)  {
		//   sem_wait(&len);
		printf("%s+:\n", __FUNCTION__);

                file = fopen("mdmconfig.txt", "r");

                if (file < 0)
			return;

		char inbuf[512];
		char *ptr;
		int lines = 0;
		while (fgets(inbuf, sizeof(inbuf), file)) {
			lines ++;
			ptr = strchr(inbuf, '\r');
			if (ptr)
				*ptr = 0;
			ptr = strchr(inbuf, '\n');
			if (ptr)
				*ptr = 0;
			if (strncmp(inbuf, CFGTAG_COMPORT, strlen(CFGTAG_COMPORT)) == 0) {
				strcpy(comport, inbuf + strlen(CFGTAG_COMPORT));
			} else
			if (strncmp(inbuf, CFGTAG_COMSPEED, strlen(CFGTAG_COMSPEED)) == 0) {
				sscanf(inbuf + strlen(CFGTAG_COMSPEED), "%d", &comspeed);
			} else
			if (strncmp(inbuf, CFGTAG_ATCOMMAND, strlen(CFGTAG_ATCOMMAND)) == 0) {
				strcat(inbuf, "\r");
				atCommands.push_back(inbuf);
			}
		}
                fclose(file);
		
		cout << "comport=" << comport << endl;
		cout << "comspeed=" << comspeed << endl;
		cout << "\tspeed values:" << "B9600:" << B9600 << ",B19200:" << B19200 << ",B38400:" << B38400 << ",B57600:" << B57600 << ",B115200:" << B115200 << endl;
		
		vector<string>::iterator it;
		it = atCommands.begin();
		while (it != atCommands.end()) {
			cout << *it << endl;
			it ++;
		}
		
	}

	void  readport(void)
	{
		char buff[256];
		int n;
		printf("%s+:\n", __FUNCTION__);
		file = fopen( "zname.txt", "w+" );
		while (1) { 
			memset(buff, 0, sizeof(buff));
			n = read(fd, buff, 200);
			//	fcntl(fd,F_SETFL,0);
			if (n == -1) switch(errno) {
				case EAGAIN: /* sleep() */ 
				continue;
          
				default: 
				goto quit;
			}
			if (n ==0) break;
//			fputc(buff, file);
//			printf("%d %c\n", n,buff);
			fwrite((const char *)buff, strlen((const char *)buff), 1, file);
			// printf("%s", buff);
			handle_nmea_message(buff);
		}
quit:
		fclose (file);
	}

	void sendport(void)
	{
		printf("%s:\n", __FUNCTION__);
		int n;
#if 0
		//   sem_wait(&len);
                file = fopen("command.txt", "r");

                //get file size

                fseek(file, 0, SEEK_END);
                fileLen = ftell(file);
                fseek(file, 0, SEEK_SET);

                tmpbuffer = (char *)malloc(fileLen + 1);

                //read file contents
                printf("Start send\n");
                fread(tmpbuffer, fileLen, 1, file);
                fclose(file);
                n = write(fd, tmpbuffer, fileLen + 1);
#endif
		vector<string>::iterator it;

		it = atCommands.begin();
		while (it != atCommands.end()) {
			cout << *it << endl;
			n = write(fd, it->c_str(), it->length());
			if (n < 0)
			{
				fputs("write() of bytes failed!\n", stderr);
			}
			else
			{
				printf(">> %s\n",it->c_str());
			}
			it ++;
			sleep(1);
		}		


	}

	void openport(void)
	{
		printf("%s+:\n", __FUNCTION__);
		fd = open(comport, O_RDWR | O_NOCTTY |O_NDELAY );
		printf("Oviya %d\n",fd);
		if (fd <0)
		{
			printf("%s port open failed: %s\n",__FUNCTION__, comport);
			perror(MODEMDEVICE);         
		}
                                                                                
		fcntl(fd,F_SETFL,0);
		tcgetattr(fd,&oldtp); /* save current serial port settings */
		// tcgetattr(fd,&newtp); /* save current serial port settings */
		bzero(&newtp, sizeof(newtp));
		// bzero(&oldtp, sizeof(oldtp));
                                                                                
		newtp.c_cflag = comspeed | CRTSCTS | CS8 | CLOCAL | CREAD;
                                                                                
		newtp.c_iflag = IGNPAR | ICRNL;
                                                                                
		newtp.c_oflag = 0;
                                                                                
		newtp.c_lflag = ICANON;
                                                                                
		newtp.c_cc[VINTR]    = 0;     /* Ctrl-c */
		newtp.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
		newtp.c_cc[VERASE]   = 0;     /* del */
		newtp.c_cc[VKILL]    = 0;     /* @ */
		//newtp.c_cc[VEOF]     = 4;     /* Ctrl-d */
		newtp.c_cc[VEOF]     = 0;     /* Ctrl-d */
		newtp.c_cc[VTIME]    = 0;     /* inter-character timer unused */
		newtp.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
		newtp.c_cc[VSWTC]    = 0;     /* '\0' */
		newtp.c_cc[VSTART]   = 0;     /* Ctrl-q */
		newtp.c_cc[VSTOP]    = 0;     /* Ctrl-s */
		newtp.c_cc[VSUSP]    = 0;     /* Ctrl-z */
		newtp.c_cc[VEOL]     = 0;     /* '\0' */
		newtp.c_cc[VREPRINT] = 0;     /* Ctrl-r */
		newtp.c_cc[VDISCARD] = 0;     /* Ctrl-u */
		newtp.c_cc[VWERASE]  = 0;     /* Ctrl-w */
		newtp.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
		newtp.c_cc[VEOL2]    = 0;     /* '\0' */
                                                                
		//     tcflush(fd, TCIFLUSH);
		//	tcsetattr(fd,TCSANOW,&newtp);
	}

	void closeport(void)
	{
		printf("%s:\n", __FUNCTION__);
		if (fd) {
			close(fd);
			fd = 0;
		}
	}
	
	void startread() {
		printf("%s+:\n", __FUNCTION__);
		workerid = pthread_create( &thread_workder, NULL, modem_reader, (void*) "thread 1");
		//pthread_join(thread_workder, NULL);
		printf("%s-:\n", __FUNCTION__);
	}
	
	void waitread() {
		printf("%s+:\n", __FUNCTION__);
		pthread_join(thread_workder, NULL);
		printf("%s-:\n", __FUNCTION__);
	}
private:


private:
	int fd;
	FILE *file;
	int fileLen;
	char *tmpbuffer;

	struct termios oldtp, newtp;
	//char sendcmd1[256]="\0";
	char buffer[512];

	pthread_t thread_workder;
	int workerid;
	
	char comport[60];
	int  comspeed;
	vector <string> atCommands;
};

ModemPort modem;

void my_handler(int s){
           printf("Caught signal %d\n",s);
	   modem.closeport();
	   show_nmea();
           exit(1); 

}

void *modem_reader(void *argument) {
	char* msg;
	msg = (char*)argument;
	std::cout<<msg<<std::endl;
	modem.readport();
	return 0;
}
	
void worker(string name) {
	cout << __FUNCTION__ << name << endl;
	modem.readport();
}
	
int main()
{

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	modem.loadconfig();
	
	modem.openport();
	sleep(1);
	modem.startread();

	//thread t1(worker, "Hello");
	//t1.join();

	modem.sendport();
	modem.waitread();
	//std::cin.get();
	//modem.readport();
	
	show_nmea();
	
	modem.closeport();
	return 0;
}

