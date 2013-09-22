#include <direct.h>
#include <dinput.h>
#include <d3dx9tex.h>
#include <Windows.h>

#ifndef RESOURCE_MANAGEMENT_H 
#define RESOURCE_MANAGEMENT_H 
  
//************************************************************************
// Resource Class - Class that gets the resource
//************************************************************************
// Each type of resource: sound, texture, etc. should have their own separate 
// resource manager class, but since our project is small in scope, it may
// not be necessary to do so, not sure on this yet.
template< class Type > class Resource 
{ 
public:  
	
	// Resource class constructor. 
	Resource( char *name, char *path = "./" ) 
	{ 
		// Store the name of the file 
		if( name != NULL ) 
		{ 
			resName = new char[strlen( name ) + 1];
			// Makes a copy of the name
			memcpy( resName, name, ( strlen( name ) + 1 ) * sizeof( char ) ); 
		} 
 
		// Store the path of the file. 
		if( path != NULL ) 
		{ 
			resPath = new char[strlen( path ) + 1];
			// Makes a copy of the path
			memcpy( resPath, path, ( strlen( path ) + 1 ) * sizeof( char ) ); 
		} 
 
		// Create the filename. 
		if( name != NULL && path != NULL ) 
		{ 
			fileName = new char[strlen( name ) + strlen( path ) + 1];
			// Writes the data as string
			sprintf( fileName, "", path, name ); 
		} 
 
		// Start the reference count. 
		m_refCount = 1; 
	} 
 
	// The resource class destructor. 
	virtual ~Resource() 
	{ 
		SAFE_DELETE_ARRAY( resName ); 
		SAFE_DELETE_ARRAY( resPath ); 
		SAFE_DELETE_ARRAY( fileName ); 
	} 
 
	// Returns the name of the resource. 
	char *GetName() { 
		return resName; 
	} 
 
	// Returns the path to the resource. 
	char *GetPath() { 
		return resPath; 
	} 
  
	// Returns the filename of the resource.  
	char *GetFilename() 
	{ 
		return fileName; 
	} 
 
	// Increments the resource's reference count.  
	void IncrementRef() 
	{ 
		m_refCount++; 
	} 
  
	// Decrements the resource's reference count.  
	void DecrementRef() 
	{ 
		m_refCount--; 
	} 
  
	// Returns the resource's reference count.  
	unsigned long GetRefCount() 
	{ 
		return m_refCount; 
	} 

// Just made up names
private: 
	char *resName; // Name of the resource. 
	char *resPath; // Path to the resource. 
	char *fileName; // Filename (name + path) of the resource. 
	unsigned long m_refCount; // Reference count. 
}; 

//*****************************************************************
// Resource Manager Class  
//*****************************************************************
template< class Type > class ResourceManager 
{ 
public: 
 
	// The resource manager class constructor. 
	ResourceManager( void (*CreateResourceFunction)( Type **resource, char *name, char *path ) = NULL ) 
	{ 
		m_list = new LinkedList< Type >; 
 
		CreateResource = CreateResourceFunction; 
	} 
 
	// The resource manager class destructor. 
	~ResourceManager() 
	{ 
		SAFE_DELETE( m_list ); 
	} 
 
	// Adds a new resource to the manager.  
	Type *Add( char *name, char *path = "./" ) 
	{ 
		// Ensure the list, the resource name, and its path are valid. 
		if( m_list == NULL || name == NULL || path == NULL ) 
			return NULL; 
 
		// If the element already exists, then return a pointer to it. 
		Type *element = GetElement( name, path ); 
		if( element != NULL ) 
		{ 
			element->IncRef(); 
			return element; 
		} 
 
		// Create the resource, preferably through the application specific 
		// function if it is available. 
		Type *resource = NULL; 
		if( CreateResource != NULL ) 
			CreateResource( &resource, name, path ); 
		else 
			resource = new Type( name, path ); 
 
		// Add the new resource to the manager and return a pointer to it. 
		return m_list->Add( resource ); 
	} 
 
	// Removes the given resource from the manager.  
	void Remove( Type **resource ) 
	{ 
		// Ensure the resource to be removed and the list is valid. 
		if( *resource == NULL || m_list == NULL ) 
			return; 
 
		// Decrement the resource's reference count. 
		(*resource)->DecRef(); 
 
		// If the resource is no long being used then destroy it. 
		if( (*resource)->GetRefCount() == 0 ) 
			m_list->Remove( resource ); 
	} 
 
	// Empties the resource list. 
	void EmptyList() 
	{ 
		if( m_list != NULL ) 
			m_list->Empty(); 
	} 
  
	// Returns the list of resources. 
	LinkedList< Type > *GetList() 
	{ 
		return m_list; 
	} 
 
	// Returns a resource by its filename. 
	Type *GetElement( char *name, char *path = "./" ) 
	{ 
		// Ensure the name and path are valid, and the list is valid and not empty. 
		if( name == NULL || path == NULL || m_list == NULL ) 
			return NULL; 
		if( m_list->GetFirst() == NULL ) 
			return NULL; 
 
		// Iterate the list looking for the specified resource. 
		m_list->Iterate( true ); 
		while( m_list->Iterate() ) 
			if( strcmp( m_list->GetCurrent()->GetName(), name ) == 0 ) 
				if( strcmp( m_list->GetCurrent()->GetPath(), path ) == 0 ) 
					return m_list->GetCurrent(); 
 
		// Return NULL if the resource was not found. 
		return NULL; 
	} 
 
private: 
	LinkedList< Type > *m_list; // Linked list of resources. 
 
	void (*CreateResource)( Type **resource, char *name, char *path ); // Application specific resource creation. 
}; 
 
#endif
