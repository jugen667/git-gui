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

//================
// - CLASSES -
//================
class GitObj
{
    private:
        git_repository *repo; // repository
        git_status_list *statuses; // status list
    public:
        // getter
        git_repository * GetCurrentGitRepo(); 
        git_repository ** GetCurrentGitRepoAddress(); 
        git_status_list * GetGitStatusList();
        git_status_list ** GetGitStatusListAddress();
        // constructor
        GitObj();
};

#endif

