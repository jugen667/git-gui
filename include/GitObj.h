//========================
// - Info -
// - Window Class
// - Author : juju80gen -
//========================

#ifndef _GITOBJ_CLASS_
#define _GITOBJ_CLASS_

//==============
// - INCLUDES -
//==============

//===============
// - PROTOTYPES -
//===============
void DisplayStatus(const git_status_entry * status_entry); 
QString ReturnStatus(const git_status_entry * status_entry);

enum index_mode {
    INDEX_NONE,
    INDEX_ADD
};

struct index_options {
    int dry_run;
    int verbose;
    git_repository *repo;
    enum index_mode mode;
    int add_update;
};

//================
// - CLASSES -
//================
class GitObj
{
    private:
        git_repository      *repo;           // repository
        git_status_list     *statuses;       // status list
        git_status_options  statusOptions;
    public:
        // getter
        git_repository      *GetCurrentGitRepo(); 
        git_status_list     *GetGitStatusList();
        git_status_list     **GetGitStatusListAddress();
        git_status_options  *GetGitStatusOpt();
        // constructor
        GitObj();
};

#endif

