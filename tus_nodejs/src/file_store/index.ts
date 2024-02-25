import { DataStore } from "utils/src/DataStore";
import { Upload } from "utils/src/Upload";

export class FileStore extends DataStore {
    constructor(directory: string) {
        super();
        this.directory = directory;
    }
    directory: string


    
    create(upload: Upload): Upload {
        const file = 
    }
}