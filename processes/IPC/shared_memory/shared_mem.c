int shmget(key_t key, size_t size, int shmflg);
// function: create a new shared mem section, the data in the section will be initialised as 0
//	parameters:
//		key: find or create a shared mem
//		size: size of the shared memory
//		shmflg: attributes of shared memory like access permisission, identify if the shared memory exist
//				IPC_CREAT : create
//				IPC_EXEL : exist or not, need to be used together with IPC_CREAT
//		return: a memory identifier, -1 on fail
//
void *shmat(int shmid, const void *shmaddr, int shmflg);
//	function: connect with process
//	parameters:
//		shmid: obtained by shmget
//		shmaddr: NULL, assigned by kernel
//		shmflg:
//			SHM_EXEC: executable
//			SHM_RDONLY: read, must have
//			SHM_REMAP
//	return: initial of address of the shared memory
//
int shmdt(const void *shmaddr);
//	function: unlink the process and shared mem
//
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
//	function: delete shared memory
//	parameters:
//		shmid
//		cmd: actions to be conduct
//			IPC_STAT: obtain the current state of the mem
//			IPC_SET: set state of the mem
//			IPC_RMID: mark remove shared mem
//		shtruct shmid_ds *buf: attributes of shared memory
//			IPC_STAT: buf to store data
//			IPC_SET: but needs to be initialised to the kernal
//			IPC_RMID: NULL
 key_t ftok(const char *pathname, int proj_id);
// 	function: according to path directory and integer to generate a key
// 	parameters:
// 		pathname: a legal path
// 		proj_id: system envoke can only use the first 8 bits of proj_id
//
// Q&A
// 1. How does the system know how many shared memory are related with processes
// 	A: Shared memory contains a structrure: struct_shmid_DS, the structure member: shm_nattach records the number of attachments
// 2. Can we multiple execute shmctl
// 	A: YEs, because shmctl only marks the deleted shared memory, not directly delete, when number of connection becomes 0 the mem deletes
// 	when key of the shared memory is 0, meaning the mem is marked delete
// 3. Shared memory and memory mapping difference
// 	A: shared mem can be directly created, mem mapping needs disk file
// 	   shared mem is more effective
// 	   All process of shared mem controls the same memory; in mapping, each process has its individual memory
// 	   Data safety: Abort: shared memory exists, mapping disappear;
// 	   		Process stuck, shared memory disappear, mapping exists becuase mapping stored in disk
// 	   Lifespan: Mapping, when process exits, mapping destroyed
// 	   	     Shared mem, when process exits, shared mem exist, marked delete
