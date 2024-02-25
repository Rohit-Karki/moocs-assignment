import EventEmitter from 'node:events';
import { Upload } from './Upload';

abstract class DataStore extends EventEmitter {
    // Creates a new file for creation extension
    // An empty POST request is used to create a new upload resource. 
    // The Upload-Length header indicates the size of the entire upload in bytes.
    create(upload: Upload) {
        return upload
    }
    // Called in patch request 
    // To handle the chunk bytes
    async write() {

    }
    // Called in delete request
    async remove(id: string) { }

    // Called in head request
    async getFileOffset(id: string) {
        // get the file length from the file store and then use that file
        // length as the offset to return as file offset


    }
}

export { DataStore }