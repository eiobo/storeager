#include <bits/stdc++.h>

using namespace std;

class MemoryPool {
private: 
    struct FreeListNode {
        FreeListNode* next;
    };
    size_t m_chunkSize;                 // size of each memory chunk
    size_t m_numTotalChunks;            // Total num of chunks managed by the pool
    FreeListNode* m_freeListHead;       // Ptr to the first free chunk in the list
    char* m_memoryBlock;                // Pointer to the large pre-allocated block of raw memory

    size_t m_numFreeChunks;
public: 
    MemoryPool(size_t chunkSize, size_t numChucks): 
        m_chunkSize(chunkSize),
        m_numTotalChunks(numChucks),
        m_memoryBlock(nullptr),
        m_freeListHead(nullptr),
        m_numFreeChunks(0) {
        
        // 确保 chunkSize 满足最大对齐要求
        size_t alignment = 4;                   // alignof(Myclass);    // 或 alignof(Myclass)
        // 让m_chunkSize成为alignment的整数倍数
        m_chunkSize = ((chunkSize + alignment - 1) / alignment) * alignment;
        if (m_chunkSize != chunkSize) {
            cerr << "Warning: chunkSize adjusted from " << chunkSize 
                << " to " << m_chunkSize << " for alignment." << endl;
        }

        // make sure the chunkSize >= sizeof(FreeListNode)
        if(m_chunkSize < sizeof(FreeListNode)) {
        cerr << "Warning: chunkSize (" << m_chunkSize << ") is too small. Increasing to " 
            << sizeof(FreeListNode) 
            << " to accommodate FreeListNode." << std::endl;
            m_chunkSize = sizeof(FreeListNode);
        }

        // counting total memory needed in Bytes size
        size_t m_totalMemoryBytesSize = m_chunkSize * m_numTotalChunks;

        // allocate raw memory 
        m_memoryBlock = new char[m_totalMemoryBytesSize];       // 返回的地址必定满足最大类型的对齐要求,也满足int的对齐要求
        if (!m_memoryBlock) throw std::bad_alloc();             // If allocation fails, throw an exception

        m_freeListHead = reinterpret_cast<FreeListNode*>(m_memoryBlock);    // first addr of pre-allocated block is the m_freeListHead
        FreeListNode* curr = m_freeListHead;
        m_numFreeChunks = 1;

        // Link free Node together
        for(size_t i = 1; i < numChucks; i++) {
            char* chunkstart = m_memoryBlock + i * m_chunkSize;
            curr->next = reinterpret_cast<FreeListNode*>(chunkstart);
            curr = curr->next;
            m_numFreeChunks++;
        }

        // Ensure the last chunk points to nullptr
        if(curr) curr->next = nullptr;

        std::cout << "[MemoryPool] Initialized: Chunk Size = " << m_chunkSize 
            << ", Total Chunks = " << m_numTotalChunks 
            << ", Total Memory = " << m_totalMemoryBytesSize << " bytes." << std::endl;
        cout << "m_freeListHead addr : " << m_freeListHead << endl;
    }
    ~MemoryPool() {
        cout << "[MemoryPool] Destroyed. Remaining free chunks: " << m_numFreeChunks << "/" << m_numTotalChunks << std::endl;
        delete[] m_memoryBlock;                         // Deallocate the entire block of memory that was pre-allocated
        m_memoryBlock = nullptr;                        // Good practice to nullify after deletion
        m_freeListHead = nullptr;
    }

    // Disable copy and assignment for the pool itself to avoid complex resource management
    // 这两行代码的作用是禁用内存池对象的拷贝构造和赋值操作：
    // 因为 MemoryPool 管理着一块独占的大内存和复杂的资源，拷贝或赋值会导致资源重复释放、内存混乱等严重问题。禁用后，编译器会阻止你做这些危险操作，保证资源安全。
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    void* allocate(size_t size) {
        if(size > m_chunkSize) {
            cerr << "[MemoryPool] Error: Requested size (" << size 
                      << ") exceeds pool chunk size (" << m_chunkSize << "). Allocation failed." << endl;
            return nullptr;                                 // Indicate failure
        }
        if (!m_freeListHead) {                              // The pool is exhausted (no free chunks left)
            cerr << "[MemoryPool] Error: Pool exhausted. Cannot allocate " << size << " bytes." << endl;
            return nullptr; // Indicate failure
        }
        
        // Take the first available free chunk
        FreeListNode* freeNode = m_freeListHead;
        m_freeListHead = freeNode->next;                    // Move the head to the next free chunk
        m_numFreeChunks--;

        // For debugging: Overwrite the 'next' pointer to a known invalid value
        // This helps detect if a chunk is accidentally re-used while still in free list.
        // freeNode->next = reinterpret_cast<FreeListNode*>(0xDEADBEEF);

        cout << "[MemoryPool] Allocated chunk at: " << static_cast<void*>(freeNode) 
                  << " (Free chunks left: " << m_numFreeChunks << "/" << m_numTotalChunks << ")" << endl;
        
        return static_cast<void*>(freeNode); // Return the raw memory chunk
    }
    void deallocate(void* ptr) {
        if (!ptr) {
            return; // Deleting a null pointer is a no-op.
        }
        // --- Enhanced Validation ---
        char* charPtr = static_cast<char*>(ptr);
        char* poolStart = static_cast<char*>(m_memoryBlock);
        char* poolEnd = poolStart + m_chunkSize * m_numTotalChunks;

        // 1. Check if the pointer is within the overall managed memory range.
        if (charPtr < poolStart || charPtr >= poolEnd) {
            std::cerr << "[MemoryPool] Error: Attempted to deallocate memory OUTSIDE the pool's managed range: " << ptr << std::endl;
            // In a real scenario, you might fall back or throw an exception.
            return;
        }

        // 2. Check if the pointer is correctly aligned to a chunk start.
        if ((charPtr - poolStart) % m_chunkSize != 0) {
            std::cerr << "[MemoryPool] Error: Attempted to deallocate memory NOT starting at a chunk boundary: " << ptr << std::endl;
            // This pointer is within the pool's memory block but not at the start of a chunk.
            return;
        }
        // --- End Enhanced Validation ---

        // TODO: !!! CRITICAL: Add double-free detection here !!!
        // For example, you might query a separate allocation status array/map,
        // or check a magic number written into the block during allocation before it was freed.
        // Without this, double-freeing is a severe vulnerability.

        // Convert the raw pointer back to a FreeListNode
        FreeListNode* nodeToFree = reinterpret_cast<FreeListNode*>(ptr);

        // Add the chunk back to the front of the free list
        nodeToFree->next = m_freeListHead;
        m_freeListHead = nodeToFree;
        m_numFreeChunks++;

        std::cout << "[MemoryPool] Deallocated chunk at: " << ptr
                << " (Free chunks available: " << m_numFreeChunks << "/" << m_numTotalChunks << ")" << std::endl;
    }

    // --- Diagnostic Getters ---
    size_t getChunkSize() const { return m_chunkSize; }
    size_t getTotalChunks() const { return m_numTotalChunks; }
    size_t getFreeChunks() const { return m_numFreeChunks; }
    size_t getUsedChunks() const { return m_numTotalChunks - m_numFreeChunks; }
};

class Myclass {
private:
    int id;
    int values[4];          // Simulating some data members
    char buffer[15];        // Another data member
    static const size_t OBJECT_CHUNK_SIZE = 36;
    static MemoryPool s_memoryPool; 

public:
    // --- Constructor ---
    Myclass(int obj_id = 0) : id(obj_id) {
        values[0] = 1; values[1] = 2; values[2] = 3; values[3] = 4;
        buffer[0] = 'a'; buffer[1] = 'b'; // Initialize some buffer data
        
        // Note: The object data is constructed AFTER memory is allocated by operator new.
        std::cout << "Myclass(" << id << ") constructed at address: " << this << std::endl;
    }

    ~Myclass() {
        std::cout << "MyObject(" << id << ") destructed at address: " << this << std::endl;
        // If Myclass itself managed dynamic memory (e.g., with `new`),
        // its destructor would be the place to `delete` those resources.
        // But here, the memory for Myclass itself comes from the pool,
        // and that's handled by operator delete.
    }

    static void* operator new(size_t size) {
        std::cout << "--> MyObject::operator new(size=" << size << ") called.\n";
        // Use the class's static memory pool to allocate memory
        void* ptr = s_memoryPool.allocate(size);
        if (!ptr) {
            // If pool allocation fails, throw std::bad_alloc, as expected by new
            throw std::bad_alloc(); 
        }
        return ptr;
    }

    // Overload operator delete for single object deallocation
    // This is called when `delete obj;` is used.
    static void operator delete(void* ptr) {
        std::cout << "--> MyObject::operator delete(ptr=" << ptr << ") called.\n";
        // Return the memory back to the pool
        s_memoryPool.deallocate(ptr);
    }

    // --- Example Member Function ---
    void displayInfo() const {
        std::cout << "  MyObject ID: " << id << " (at " << this << ")" << std::endl;
    }

    // --- Static accessors for pool info ---
    static size_t getPoolChunkSize() { return s_memoryPool.getChunkSize(); }
    static size_t getPoolTotalChunks() { return s_memoryPool.getTotalChunks(); }
    static size_t getPoolFreeChunks() { return s_memoryPool.getFreeChunks(); }
    static size_t getPoolUsedChunks() { return s_memoryPool.getUsedChunks(); }
};

// --- DEFINITION of the static members ---
// This is where the MemoryPool is actually created.
// We initialize it with 10 chunks, each 36 bytes.
MemoryPool Myclass::s_memoryPool(Myclass::OBJECT_CHUNK_SIZE, 10);

int main() {
    std::cout << "--- Starting Memory Pool Demo ---\n\n";
    std::cout << "Initial Pool State: \n";
    std::cout << "  Chunk Size: " << Myclass::getPoolChunkSize() << " bytes\n";
    std::cout << "  Total Chunks: " << Myclass::getPoolTotalChunks() << "\n";
    std::cout << "  Free Chunks: " << Myclass::getPoolFreeChunks() << "\n";
    std::cout << "  Used Chunks: " << Myclass::getPoolUsedChunks() << "\n\n";

    std::cout << "--- Allocating First Batch of Objects ---\n";
    Myclass* obj1 = nullptr;
    Myclass* obj2 = nullptr;
    Myclass* obj3 = nullptr;

    try {
        obj1 = new Myclass(1);
        obj2 = new Myclass(2);
        obj3 = new Myclass(3);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Caught exception during allocation: " << e.what() << std::endl;
    }

    std::cout << "\nPool State After Allocations:\n";
    std::cout << "  Free Chunks: " << Myclass::getPoolFreeChunks() << "\n";
    std::cout << "  Used Chunks: " << Myclass::getPoolUsedChunks() << "\n\n";

    // 刚好中间相差36字节
    if (obj1) obj1->displayInfo();
    if (obj2) obj2->displayInfo();
    if (obj3) obj3->displayInfo();

    // 删除某些对象
    std::cout << "\n--- Deallocating Some Objects ---\n";
    delete obj1; // Calls MyObject::operator delete
    obj1 = nullptr; 

    delete obj2; // Calls MyObject::operator delete
    obj2 = nullptr;

    std::cout << "\nPool State After Deallocations:\n";
    std::cout << "  Free Chunks: " << Myclass::getPoolFreeChunks() << "\n";
    std::cout << "  Used Chunks: " << Myclass::getPoolUsedChunks() << "\n\n";

    // 重复利用
    std::cout << "--- Allocating Second Batch (to show reuse) ---\n";
    Myclass* obj4 = nullptr;
    Myclass* obj5 = nullptr;

    try {
        obj4 = new Myclass(4);
        obj5 = new Myclass(5);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Caught exception during allocation: " << e.what() << std::endl;
    }

    std::cout << "\nPool State After Second Batch Allocations:\n";
    std::cout << "  Free Chunks: " << Myclass::getPoolFreeChunks() << "\n";
    std::cout << "  Used Chunks: " << Myclass::getPoolUsedChunks() << "\n\n";

    // 清理
    delete obj3;
    delete obj4;
    delete obj5;

    std::cout << "--- Testing Pool Exhaustion ---\n";
    // Let's try to allocate more objects than the pool's initial capacity (10 chunks)
    // We will allocate up to 12 objects to demonstrate depletion.
    const int EXTRA_ALLOCATIONS = 12; 
    std::vector<Myclass*> extraObjects;

    std::cout << "Attempting to allocate " << EXTRA_ALLOCATIONS << " more objects...\n";
    for (int i = 0; i < EXTRA_ALLOCATIONS; ++i) {
        Myclass* obj = nullptr;
        try {
            obj = new Myclass(100 + i); // IDs start from 100
            extraObjects.push_back(obj);
            std::cout << "Successfully allocated Myclass(" << (100 + i) << ") at " << obj << std::endl;
        } catch (const std::bad_alloc& e) {
            std::cerr << ">>>> Failed to allocate Myclass(" << (100 + i) << ") due to pool exhaustion: " << e.what() << std::endl;
            // Stop trying to allocate if pool is exhausted
            break; 
        }
    }

    std::cout << "\nPool State After Exhaustion Test:\n";
    std::cout << "  Free Chunks: " << Myclass::getPoolFreeChunks() << "\n";
    std::cout << "  Used Chunks: " << Myclass::getPoolUsedChunks() << "\n\n";

    // Clean up any objects that were successfully allocated in the last loop
    for (Myclass* obj : extraObjects) delete obj;
    extraObjects.clear();

    std::cout << "\n--- End of Demo ---\n";

    return 0;
}
