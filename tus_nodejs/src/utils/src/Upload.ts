type TUpload = {
    id: string,
    fileName: string,
    size?: number,
    incompleteFileUploadSize?: number,
    creationDate?: string,
}
export class Upload {
    constructor(tUpload: TUpload) {
        this.id = tUpload.id;
        this.fileName = tUpload.fileName;
        this.size = tUpload.size;
        this.incompleteFileUploadSize = tUpload.incompleteFileUploadSize;
        this.creationDate = tUpload.creationDate ?? new Date().toISOString();
    }
    id: TUpload['id'];
    fileName: TUpload['fileName'];
    size?: TUpload['size'];
    incompleteFileUploadSize?: TUpload['incompleteFileUploadSize']
    creationDate?: TUpload['creationDate'];

    isFileSizeDefferred(): boolean {
        return this.size === undefined
    }
}