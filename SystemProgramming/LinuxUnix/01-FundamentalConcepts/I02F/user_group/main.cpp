#include <iostream>
#include <print>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    // Real and effective user and group IDs
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    gid_t real_gid = getgid();
    gid_t effective_gid = getegid();

    println("Real UID:      {}", real_uid);
    println("Effective UID: {}", effective_uid);
    println("Real GID:      {}", real_gid);
    println("Effective GID: {}", effective_gid);

    // Supplementary group IDs
    int ngroups = getgroups(0, NULL);  // Get the number of supplementary groups
    if (ngroups == -1) {
      cerr << "Error on getgroups call\n";
      return EXIT_FAILURE;
    }

    gid_t groups[ngroups];
    if (getgroups(ngroups, groups) == -1) {
      cerr << "Error on getgroups call\n";
      return EXIT_FAILURE;
    }

    println("Supplementary groups:");
    for (int i = 0; i < ngroups; i++) {
        println("\tGID: {}", groups[i]);
    }

    return EXIT_SUCCESS;
}

