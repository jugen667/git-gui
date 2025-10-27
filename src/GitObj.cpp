//========================
// - Info -
// - about -
// - File -
// - Author : juju80gen -
//========================

//==============
// - INCLUDES -
//==============
#include "../include/includes.h"

//===============
// - FUNCTIONS -
//===============
void DisplayStatus(const git_status_entry * status_entry)
{
    switch (status_entry->status)
    {
        case GIT_STATUS_WT_NEW :
            std::cout <<  "new file: " << status_entry->index_to_workdir->old_file.path << std::endl;
        break;
        case GIT_STATUS_WT_MODIFIED:
            std::cout << "modified: " << status_entry->index_to_workdir->old_file.path << std::endl;
        break;
        case GIT_STATUS_WT_DELETED:
            std::cout << "deleted:  " << status_entry->index_to_workdir->old_file.path << std::endl;
        break;
        case GIT_STATUS_WT_RENAMED:
            std::cout << "renamed:  " << status_entry->index_to_workdir->old_file.path << "\t->\t" << status_entry->index_to_workdir->new_file.path << std::endl;
        break;
        case GIT_STATUS_WT_TYPECHANGE:
            std::cout << "typechange:" << status_entry->index_to_workdir->old_file.path << "\t->\t" << status_entry->index_to_workdir->new_file.path << std::endl;
        break;
        case GIT_STATUS_IGNORED:
            std::cout << "ignored:" << status_entry->index_to_workdir->old_file.path << std::endl;
        break;
        default :
           std::cout <<  status_entry->status << std::endl; 
        break;
    }
}

QString ReturnStatus(const git_status_entry * status_entry)
{
    switch (status_entry->status)
    {
        case GIT_STATUS_WT_NEW : 
            return "new";
        break;
        case GIT_STATUS_WT_MODIFIED:
            return "modified";
        break;
        case GIT_STATUS_WT_DELETED:
            return "deleted";
        break;
        case GIT_STATUS_WT_RENAMED:
            return "renamed";
        break;        
        case GIT_STATUS_WT_TYPECHANGE:
            return "typechange";
        break;
        case GIT_STATUS_IGNORED:
            return "ignored";
        break;
        default :
            return NULL;
        break;
    }
}


//===============
// - METHODS -
//===============

// git object construction
GitObj::GitObj() 
{
    // fields initialization
    repo = NULL;
    statuses = NULL;

    // status options init
    statusOptions = GIT_STATUS_OPTIONS_INIT;
    statusOptions.flags = (GIT_STATUS_OPT_INCLUDE_UNTRACKED | GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS);

    // init the repo the bin is in
    git_repository_open(&repo,".");
}

// getters
git_repository * GitObj::GetCurrentGitRepo()
{
    return (GitObj::repo);
}

git_status_list * GitObj::GetGitStatusList()
{
    return (GitObj::statuses);
}

git_status_list ** GitObj::GetGitStatusListAddress()
{
    return &(GitObj::statuses);
} 

git_status_options * GitObj::GetGitStatusOpt()
{
    return &(GitObj::statusOptions);
} 
