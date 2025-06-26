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
// - METHODS -
//===============

// main window construction
GitObj::GitObj() 
{
    // fields initialization
    repo = NULL;
    statuses = NULL;
}

// getters
git_repository * GitObj::GetCurrentGitRepo()
{
    return (GitObj::repo);
}
git_repository ** GitObj::GetCurrentGitRepoAddress()
{
    return &(GitObj::repo);
} 

git_status_list * GitObj::GetGitStatusList()
{
    return (GitObj::statuses);
} 
git_status_list ** GitObj::GetGitStatusListAddress()
{
    return &(GitObj::statuses);
} 