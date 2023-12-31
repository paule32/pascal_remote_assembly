// --------------------------------------------------------------------
// File:   GetLastError.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
//
// @brief This file contains the Microsoft Windows 10 error codes, that
//        can be use in context with the win32api member "GetLastError"
//        The error code will be map'ed into a std::map list in origin
//        language of en_US.
//        To use in your own application, you can use the po/mo locale
//        files for localization. You can find these files as attached.
//
//        Feel free, and drop a message, if you find mistakes/error's.
// --------------------------------------------------------------------
extern "C" {
# include <windows.h>   // DWORD, ...

# include <libintl.h>   // locale: gettext
# include <locale.h>    // localization
};

// --------------------------------------------------------------------
// C++ standard header stuff ...
// --------------------------------------------------------------------
# include <iostream>
# include <string>      // std::string
# include <map>         // std::map

std::map< DWORD, std::string > WindowsErrorCode =
{
    { ERROR_SUCCESS,"The operation completed successfully." },
    { ERROR_INVALID_FUNCTION,"Incorrect function." },
    { ERROR_FILE_NOT_FOUND,"The system cannot find the file specified." },
    { ERROR_PATH_NOT_FOUND,"The system cannot find the path specified." },
    { ERROR_TOO_MANY_OPEN_FILES,"The system cannot open the file." },
    { ERROR_ACCESS_DENIED,"Access is denied." },
    { ERROR_INVALID_HANDLE,"The handle is invalid." },
    { ERROR_ARENA_TRASHED,"The storage control blocks were destroyed." },
    { ERROR_NOT_ENOUGH_MEMORY,"Not enough memory resources are available to process this command." },
    { ERROR_INVALID_BLOCK,"The storage control block address is invalid." },
    { ERROR_BAD_ENVIRONMENT,"The environment is incorrect." },
    { ERROR_BAD_FORMAT,"An attempt was made to load a program with an incorrect format." },
    { ERROR_INVALID_ACCESS,"The access code is invalid." },
    { ERROR_INVALID_DATA,"The data is invalid." },
    { ERROR_OUTOFMEMORY,"Not enough storage is available to complete this operation." },
    { ERROR_INVALID_DRIVE,"The system cannot find the drive specified." },
    { ERROR_CURRENT_DIRECTORY,"The directory cannot be removed." },
    { ERROR_NOT_SAME_DEVICE,"The system cannot move the file to a different disk drive." },
    { ERROR_NO_MORE_FILES,"There are no more files." },
    { ERROR_WRITE_PROTECT,"The media is write protected." },
    { ERROR_BAD_UNIT,"The system cannot find the device specified." },
    { ERROR_NOT_READY,"The device is not ready." },
    { ERROR_BAD_COMMAND,"The device does not recognize the command." },
    { ERROR_CRC,"Data error (cyclic redundancy check)." },
    { ERROR_BAD_LENGTH,"The program issued a command but the command length is incorrect." },
    { ERROR_SEEK,"The drive cannot locate a specific area or track on the disk." },
    { ERROR_NOT_DOS_DISK,"The specified disk or diskette cannot be accessed." },
    { ERROR_SECTOR_NOT_FOUND,"The drive cannot find the sector requested." },
    { ERROR_OUT_OF_PAPER,"The printer is out of paper." },
    { ERROR_WRITE_FAULT,"The system cannot write to the specified device." },
    { ERROR_READ_FAULT,"The system cannot read from the specified device." },
    { ERROR_GEN_FAILURE,"A device attached to the system is not functioning." },
    { ERROR_SHARING_VIOLATION,"The process cannot access the file because it is being used by another process." },
    { ERROR_LOCK_VIOLATION,"The process cannot access the file because another process has locked a portion of the file." },
    { ERROR_WRONG_DISK,"The wrong diskette is in the drive. Insert %2 (Volume Serial Number: %3) into drive %1." },
    { ERROR_SHARING_BUFFER_EXCEEDED,"Too many files opened for sharing." },
    { ERROR_HANDLE_EOF,"Reached the end of the file." },
    { ERROR_HANDLE_DISK_FULL,"The disk is full." },
    { ERROR_NOT_SUPPORTED,"The request is not supported." },
    { ERROR_REM_NOT_LIST,
    "Windows cannot find the network path. Verify that the network path is "
    "correct and the destination computer is not busy or turned off. If Windows "
    "still cannot find the network path, contact your network administrator." },
    { ERROR_DUP_NAME,
    "You were not connected because a duplicate name exists on the network. "
    "If joining a domain, go to System in Control Panel to change the computer "
    "name and try again. If joining a workgroup, choose another workgroup name." },
    { ERROR_BAD_NETPATH,"The network path was not found." },
    { ERROR_NETWORK_BUSY,"The network is busy." },
    { ERROR_DEV_NOT_EXIST,"The specified network resource or device is no longer available." },
    { ERROR_TOO_MANY_CMDS,"The network BIOS command limit has been reached." },
    { ERROR_ADAP_HDW_ERR,"A network adapter hardware error occurred." },
    { ERROR_BAD_NET_RESP,"The specified server cannot perform the requested operation." },
    { ERROR_UNEXP_NET_ERR,"An unexpected network error occurred." },
    { ERROR_BAD_REM_ADAP,"The remote adapter is not compatible." },
    { ERROR_PRINTQ_FULL,"The printer queue is full." },
    { ERROR_NO_SPOOL_SPACE,"Space to store the file waiting to be printed is not available on the server." },
    { ERROR_PRINT_CANCELLED,"Your file waiting to be printed was deleted." },
    { ERROR_NETNAME_DELETED,"The specified network name is no longer available." },
    { ERROR_NETWORK_ACCESS_DENIED,"Network access is denied." },
    { ERROR_BAD_DEV_TYPE,"The network resource type is not correct." },
    { ERROR_BAD_NET_NAME,"The network name cannot be found." },
    { ERROR_TOO_MANY_NAMES,"The name limit for the local computer network adapter card was exceeded." },
    { ERROR_TOO_MANY_SESS,"The network BIOS session limit was exceeded." },
    { ERROR_SHARING_PAUSED,"The remote server has been paused or is in the process of being started." },
    { ERROR_REQ_NOT_ACCEP,
    "No more connections can be made to this remote computer at this time "
    "because there are already as many connections as the computer can accept." },
    { ERROR_REDIR_PAUSED,"The specified printer or disk device has been paused." },
    { ERROR_FILE_EXISTS,"The file exists." },
    { ERROR_CANNOT_MAKE,"The directory or file cannot be created." },
    { ERROR_FAIL_I24,"Fail on INT 24." },
    { ERROR_OUT_OF_STRUCTURES,"Storage to process this request is not available." },
    { ERROR_ALREADY_ASSIGNED,"The local device name is already in use." },
    { ERROR_INVALID_PASSWORD,"The specified network password is not correct." },
    { ERROR_INVALID_PARAMETER,"The parameter is incorrect." },
    { ERROR_NET_WRITE_FAULT,"A write fault occurred on the network." },
    { ERROR_NO_PROC_SLOTS,"The system cannot start another process at this time." },
    { ERROR_TOO_MANY_SEMAPHORES,"Cannot create another system semaphore." },
    { ERROR_EXCL_SEM_ALREADY_OWNED,"The exclusive semaphore is owned by another process." },
    { ERROR_SEM_IS_SET,"The semaphore is set and cannot be closed." },
    { ERROR_TOO_MANY_SEM_REQUESTS,"The semaphore cannot be set again." },
    { ERROR_INVALID_AT_INTERRUPT_TIME,"Cannot request exclusive semaphores at interrupt time." },
    { ERROR_SEM_OWNER_DIED,"The previous ownership of this semaphore has ended." },
    { ERROR_SEM_USER_LIMIT,"Insert the diskette for drive %1." },
    { ERROR_DISK_CHANGE,"The program stopped because an alternate diskette was not inserted." },
    { ERROR_DRIVE_LOCKED,"The disk is in use or locked by another process." },
    { ERROR_BROKEN_PIPE,"The pipe has been ended." },
    { ERROR_OPEN_FAILED,"The system cannot open the device or file specified." },
    { ERROR_BUFFER_OVERFLOW,"The file name is too long." },
    { ERROR_DISK_FULL,"There is not enough space on the disk." },
    { ERROR_NO_MORE_SEARCH_HANDLES,"No more internal file identifiers available." },
    { ERROR_INVALID_TARGET_HANDLE,"The target internal file identifier is incorrect." },
    { ERROR_INVALID_CATEGORY,"The IOCTL call made by the application program is not correct." },
    { ERROR_INVALID_VERIFY_SWITCH,"The verify-on-write switch parameter value is not correct." },
    { ERROR_BAD_DRIVER_LEVEL,"The system does not support the command requested." },
    { ERROR_CALL_NOT_IMPLEMENTED,"This function is not supported on this system." },
    { ERROR_SEM_TIMEOUT,"The semaphore timeout period has expired." },
    { ERROR_INSUFFICIENT_BUFFER,"The data area passed to a system call is too small." },
    { ERROR_INVALID_NAME,"The filename, directory name, or volume label syntax is incorrect." },
    { ERROR_INVALID_LEVEL,"The system call level is not correct." },
    { ERROR_NO_VOLUME_LABEL,"The disk has no volume label." },
    { ERROR_MOD_NOT_FOUND,"The specified module could not be found." },
    { ERROR_PROC_NOT_FOUND,"The specified procedure could not be found." },
    { ERROR_WAIT_NO_CHILDREN,"There are no child processes to wait for." },
    { ERROR_CHILD_NOT_COMPLETE,"The %1 application cannot be run in Win32 mode." },
    { ERROR_DIRECT_ACCESS_HANDLE,
    "Attempt to use a file handle to an open disk partition for an operation "
    "other than raw disk I/O." },
    { ERROR_NEGATIVE_SEEK,"An attempt was made to move the file pointer before the beginning of the file." },
    { ERROR_SEEK_ON_DEVICE,"The file pointer cannot be set on the specified device or file." },
    { ERROR_IS_JOIN_TARGET,
    "A JOIN or SUBST command cannot be used for a drive that contains "
    "previously joined drives." },
    { ERROR_IS_JOINED,
    "An attempt was made to use a JOIN or SUBST command on a drive that has "
    "already been joined." },
    { ERROR_IS_SUBSTED,
    "An attempt was made to use a JOIN or SUBST command on a drive that has "
    "already been substituted." },
    { ERROR_NOT_JOINED,"The system tried to delete the JOIN of a drive that is not joined." },
    { ERROR_NOT_SUBSTED,
    "The system tried to delete the substitution of a drive that is not "
    "substituted." },
    { ERROR_JOIN_TO_JOIN,"The system tried to join a drive to a directory on a joined drive." },
    { ERROR_SUBST_TO_SUBST,
    "The system tried to substitute a drive to a directory on a substituted drive." },
    { ERROR_JOIN_TO_SUBST,"The system tried to join a drive to a directory on a substituted drive." },
    { ERROR_SUBST_TO_JOIN,"The system tried to SUBST a drive to a directory on a joined drive." },
    { ERROR_BUSY_DRIVE,"The system cannot perform a JOIN or SUBST at this time." },
    { ERROR_SAME_DRIVE,
    "The system cannot join or substitute a drive to or for a directory "
    "on the same drive." },
    { ERROR_DIR_NOT_ROOT,"The directory is not a subdirectory of the root directory." },
    { ERROR_DIR_NOT_EMPTY,"The directory is not empty." },
    { ERROR_IS_SUBST_PATH,"The path specified is being used in a substitute." },
    { ERROR_IS_JOIN_PATH,"Not enough resources are available to process this command." },
    { ERROR_PATH_BUSY,"The path specified cannot be used at this time." },
    { ERROR_IS_SUBST_TARGET,
    "An attempt was made to join or substitute a drive for which a "
    "directory on the drive is the target of a previous substitute." },
    { ERROR_SYSTEM_TRACE,
    "System trace information was not specified in your CONFIG.SYS "
    "file, or tracing is disallowed." },
    { ERROR_INVALID_EVENT_COUNT,
    "The number of specified semaphore events for DosMuxSemWait is "
    "not correct." },
    { ERROR_TOO_MANY_MUXWAITERS,"DosMuxSemWait did not execute; too many semaphores are already set." },
    { ERROR_INVALID_LIST_FORMAT,"The DosMuxSemWait list is not correct." },
    { ERROR_LABEL_TOO_LONG,
    "The volume label you entered exceeds the label character limit of "
    "the target file system." },
    { ERROR_TOO_MANY_TCBS,"Cannot create another thread." },
    { ERROR_SIGNAL_REFUSED,"The recipient process has refused the signal." },
    { ERROR_DISCARDED,"The segment is already discarded and cannot be locked." },
    { ERROR_NOT_LOCKED,"The segment is already unlocked." },
    { ERROR_BAD_THREADID_ADDR,"The address for the thread ID is not correct." },
    { ERROR_BAD_ARGUMENTS,"One or more arguments are not correct." },
    { ERROR_BAD_PATHNAME,"The specified path is invalid." },
    { ERROR_SIGNAL_PENDING,"A signal is already pending." },
    { ERROR_MAX_THRDS_REACHED,"No more threads can be created in the system." },
    { ERROR_LOCK_FAILED,"Unable to lock a region of a file." },
    { ERROR_BUSY,"The requested resource is in use." },
    { ERROR_DEVICE_SUPPORT_IN_PROGRESS,"Device's command support detection is in progress." },
    { ERROR_CANCEL_VIOLATION,"A lock request was not outstanding for the supplied cancel region." },
    { ERROR_ATOMIC_LOCKS_NOT_SUPPORTED,"The file system does not support atomic changes to the lock type." },
    { ERROR_INVALID_SEGMENT_NUMBER,"The system detected a segment number that was not correct." },
    { ERROR_INVALID_ORDINAL,"The operating system cannot run %1." },
    { ERROR_ALREADY_EXISTS,"Cannot create a file when that file already exists." },
    { ERROR_INVALID_FLAG_NUMBER,"The flag passed is not correct." },
    { ERROR_SEM_NOT_FOUND,"The specified system semaphore name was not found." },
    { ERROR_INVALID_STARTING_CODESEG,"The operating system cannot run %1." },
    { ERROR_INVALID_STACKSEG,"The operating system cannot run %1." },
    { ERROR_INVALID_MODULETYPE,"The operating system cannot run %1." },
    { ERROR_INVALID_EXE_SIGNATURE,"Cannot run %1 in Win32 mode." },
    { ERROR_EXE_MARKED_INVALID,"The operating system cannot run %1." },
    { ERROR_BAD_EXE_FORMAT,"%1 is not a valid Win32 application." },
    { ERROR_ITERATED_DATA_EXCEEDS_64k,"The operating system cannot run %1." },
    { ERROR_INVALID_MINALLOCSIZE,"The operating system cannot run %1." },
    { ERROR_DYNLINK_FROM_INVALID_RING,"The operating system cannot run this application program." },
    { ERROR_IOPL_NOT_ENABLED,"The operating system is not presently configured to run this application." },
    { ERROR_INVALID_SEGDPL,"The operating system cannot run %1." },
    { ERROR_AUTODATASEG_EXCEEDS_64k,"The operating system cannot run this application program." },
    { ERROR_RING2SEG_MUST_BE_MOVABLE,"The code segment cannot be greater than or equal to 64K." },
    { ERROR_RELOC_CHAIN_XEEDS_SEGLIM,"The operating system cannot run %1." },
    { ERROR_INFLOOP_IN_RELOC_CHAIN,"The operating system cannot run %1."
    { ERROR_ENVVAR_NOT_FOUND,"The system could not find the environment option that was entered." },
    { ERROR_NO_SIGNAL_SENT,"No process in the command subtree has a signal handler." },
    { ERROR_FILENAME_EXCED_RANGE,"The filename or extension is too long." },
    { ERROR_RING2_STACK_IN_USE,"The ring 2 stack is in use." },
    { ERROR_META_EXPANSION_TOO_LONG,
    "The global filename characters, * or ?, are entered incorrectly or too many "
    "global filename characters are specified." },
    { ERROR_INVALID_SIGNAL_NUMBER,"The signal being posted is not correct." },
    { ERROR_THREAD_1_INACTIVE,"The signal handler cannot be set." },
    { ERROR_LOCKED,"The segment is locked and cannot be reallocated." },
    { ERROR_TOO_MANY_MODULES,"Too many dynamic-link modules are attached to this program or dynamic-link module." },
    { ERROR_NESTING_NOT_ALLOWED,"Cannot nest calls to LoadModule." },
    { ERROR_EXE_MACHINE_TYPE_MISMATCH,
    "This version of %1 is not compatible with the version of Windows you're running. "
    "Check your computer's system information and then contact the software publisher." },
    { ERROR_EXE_CANNOT_MODIFY_SIGNED_BINARY,"The image file %1 is signed, unable to modify." },
    { ERROR_EXE_CANNOT_MODIFY_STRONG_SIGNED_BINARY,"The image file %1 is strong signed, unable to modify." },
    { ERROR_FILE_CHECKED_OUT,"This file is checked out or locked for editing by another user." },
    { ERROR_CHECKOUT_REQUIRED,"The file must be checked out before saving changes." },
    { ERROR_BAD_FILE_TYPE,"The file type being saved or retrieved has been blocked." },
    { ERROR_FILE_TOO_LARGE,"The file size exceeds the limit allowed and cannot be saved." },
    { ERROR_FORMS_AUTH_REQUIRED,
    "Access Denied. Before opening files in this location, you must first add the web "
    "site to your trusted sites list, browse to the web site, and select the option to "
    "login automatically." },
    { ERROR_VIRUS_INFECTED,
    "Operation did not complete successfully because the file contains a virus or "
    "potentially unwanted software." },
    { ERROR_VIRUS_DELETED,
    "This file contains a virus or potentially unwanted software and cannot be opened. "
    "Due to the nature of this virus or potentially unwanted software, "
    "the file has been removed from this location." },
    { ERROR_PIPE_LOCAL,"The pipe is local." },
    { ERROR_BAD_PIPE,"The pipe state is invalid." },
    { ERROR_PIPE_BUSY,"All pipe instances are busy." },
    { ERROR_NO_DATA,"The pipe is being closed." },
    { ERROR_PIPE_NOT_CONNECTED,"No process is on the other end of the pipe." },
    { ERROR_MORE_DATA,"More data is available." },
    { ERROR_VC_DISCONNECTED,"The session was canceled." },
    { ERROR_INVALID_EA_NAME,"The specified extended attribute name was invalid." },
    { ERROR_EA_LIST_INCONSISTENT,"The extended attributes are inconsistent." },
    { WAIT_TIMEOUT,"The wait operation timed out." },
    { ERROR_NO_MORE_ITEMS,"No more data is available." },
    { ERROR_CANNOT_COPY,"The copy functions cannot be used." },
    { ERROR_DIRECTORY,"The directory name is invalid." },
    { ERROR_EAS_DIDNT_FIT,"The extended attributes did not fit in the buffer." },
    { ERROR_EA_FILE_CORRUPT,"The extended attribute file on the mounted file system is corrupt." },
    { ERROR_EA_TABLE_FULL,"The extended attribute table file is full." },
    { ERROR_INVALID_EA_HANDLE,"The specified extended attribute handle is invalid." },
    { ERROR_EAS_NOT_SUPPORTED,"The mounted file system does not support extended attributes." },
    { ERROR_NOT_OWNER,"Attempt to release mutex not owned by caller." },
    { ERROR_TOO_MANY_POSTS,"Too many posts were made to a semaphore." },
    { ERROR_PARTIAL_COPY,"Only part of a ReadProcessMemory or WriteProcessMemory request was completed." },
    { ERROR_OPLOCK_NOT_GRANTED,"The oplock request is denied." },
    { ERROR_INVALID_OPLOCK_PROTOCOL,"An invalid oplock acknowledgment was received by the system." },
    { ERROR_DISK_TOO_FRAGMENTED,"The volume is too fragmented to complete this operation." },
    { ERROR_DELETE_PENDING,"The file cannot be opened because it is in the process of being deleted." },
    { ERROR_INCOMPATIBLE_WITH_GLOBAL_SHORT_NAME_REGISTRY_SETTING,
    "Short name settings may not be changed on this volume due to the global "
    "registry setting." },
    { ERROR_SHORT_NAMES_NOT_ENABLED_ON_VOLUME,"Short names are not enabled on this volume." },
    { ERROR_SECURITY_STREAM_IS_INCONSISTENT,
    "The security stream for the given volume is in an inconsistent state. "
    "Please run CHKDSK on the volume." },
    { ERROR_INVALID_LOCK_RANGE,"A requested file lock operation cannot be processed due to an invalid byte range." },
    { ERROR_IMAGE_SUBSYSTEM_NOT_PRESENT,"The subsystem needed to support the image type is not present." },
    { ERROR_NOTIFICATION_GUID_ALREADY_DEFINED,"The specified file already has a notification GUID associated with it." },
    { ERROR_INVALID_EXCEPTION_HANDLER,"An invalid exception handler routine has been detected." },
    { ERROR_DUPLICATE_PRIVILEGES,"Duplicate privileges were specified for the token." },
    { ERROR_NO_RANGES_PROCESSED,"No ranges for the specified operation were able to be processed." },
    { ERROR_NOT_ALLOWED_ON_SYSTEM_FILE,"Operation is not allowed on a file system internal file." },
    { ERROR_DISK_RESOURCES_EXHAUSTED,"The physical resources of this disk have been exhausted." },
    { ERROR_INVALID_TOKEN,"The token representing the data is invalid." },
    { ERROR_DEVICE_FEATURE_NOT_SUPPORTED,"The device does not support the command feature." },
    { ERROR_MR_MID_NOT_FOUND,
    "The system cannot find message text for message number 0x%1 in the message "
    "file for %2." },
    { ERROR_SCOPE_NOT_FOUND,"The scope specified was not found." },
    { ERROR_UNDEFINED_SCOPE,"The Central Access Policy specified is not defined on the target machine." },
    { ERROR_INVALID_CAP,"The Central Access Policy obtained from Active Directory is invalid." },
    { ERROR_DEVICE_UNREACHABLE,"The device is unreachable." },
    { ERROR_DEVICE_NO_RESOURCES,"The target device has insufficient resources to complete the operation." },
    { ERROR_DATA_CHECKSUM_ERROR,"A data integrity checksum error occurred. Data in the file stream is corrupt." },
    { ERROR_INTERMIXED_KERNEL_EA_OPERATION,
    "An attempt was made to modify both a KERNEL and normal Extended Attribute "
    "(EA) in the same operation." },
    { ERROR_FILE_LEVEL_TRIM_NOT_SUPPORTED,"Device does not support file-level TRIM." },
    { ERROR_OFFSET_ALIGNMENT_VIOLATION,
    "The command specified a data offset that does not align to the device's "
    "granularity/alignment." },
    { ERROR_INVALID_FIELD_IN_PARAMETER_LIST,"The command specified an invalid field in its parameter list." },
    { ERROR_OPERATION_IN_PROGRESS,"An operation is currently in progress with the device." },
    { ERROR_BAD_DEVICE_PATH,
    "An attempt was made to send down the command via an invalid path to the "
    "target device." },
    { ERROR_TOO_MANY_DESCRIPTORS,
    "The command specified a number of descriptors that exceeded the maximum "
    "supported by the device." },
    { ERROR_SCRUB_DATA_DISABLED,"Scrub is disabled on the specified file." },
    { ERROR_NOT_REDUNDANT_STORAGE,"The storage device does not provide redundancy." },
    { ERROR_RESIDENT_FILE_NOT_SUPPORTED,"An operation is not supported on a resident file." },
    { ERROR_COMPRESSED_FILE_NOT_SUPPORTED,"An operation is not supported on a compressed file." },
    { ERROR_DIRECTORY_NOT_SUPPORTED,"An operation is not supported on a directory." },
    { ERROR_NOT_READ_FROM_COPY,"The specified copy of the requested data could not be read." },
    { ERROR_FAIL_NOACTION_REBOOT,"No action was taken as a system reboot is required." },
    { ERROR_FAIL_SHUTDOWN,"The shutdown operation failed." },
    { ERROR_FAIL_RESTART,"The restart operation failed." },
    { ERROR_MAX_SESSIONS_REACHED,"The maximum number of sessions has been reached." },
    { ERROR_THREAD_MODE_ALREADY_BACKGROUND,"The thread is already in background processing mode." },
    { ERROR_THREAD_MODE_NOT_BACKGROUND,"The thread is not in background processing mode." },
    { ERROR_PROCESS_MODE_ALREADY_BACKGROUND,"The process is already in background processing mode." },
    { ERROR_PROCESS_MODE_NOT_BACKGROUND,"The process is not in background processing mode." },
    { ERROR_INVALID_ADDRESS,"Attempt to access invalid address." }
};

// -------------------------------------------------------------------
// @brief This function returns the error code string as std::string
//        depend on the give code.
//
// @param  DWORD        The "GetLastError" error code
// @return std::string  The maped error text
// -------------------------------------------------------------------
std::string getErrorCode(DWORD code)
{
    auto it = WindowsErrorCode.find(code);
    if (it != WindowsErrorCode.end()) {
        return gettext(it -> second() );
    }   return std::string("error unknown");
}
