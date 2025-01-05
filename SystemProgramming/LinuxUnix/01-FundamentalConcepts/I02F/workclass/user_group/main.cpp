#include <iostream>
#include <print>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
	uid_t real_user_id  = getuid();
	gid_t real_group_id = getgid();
	uid_t effective_user_id = geteuid();
	gid_t effective_group_id = getegid();

	println("Real User ID:       {}", real_user_id);
	println("Real Group ID:      {}", real_group_id);
	println("Effective User ID:  {}", effective_user_id);
	println("Effective Group ID: {}", effective_group_id);

	int ngroups = getgroups(0, NULL);
	if (ngroups == -1) {
		cerr << "Error on getgroups call\n";
		return EXIT_FAILURE;
	}

	gid_t groups[ngroups];
	if (getgroups(ngroups, groups) == -1) {
		cerr << "Error on getgroups call\n";
		return EXIT_FAILURE;
	}

	println("Supplementary Groups");
	for (gid_t groupId: groups) {
		println("\t{}", groupId);
	}


	return EXIT_SUCCESS;
}
