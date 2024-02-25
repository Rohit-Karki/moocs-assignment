import type http from 'node:http';
type urlType = {
    protocol: string;
    host: string;
    path: string;
    id: string;
}
export type ServerOptions = {

    path: string;
    generateUrl?(req: http.IncomingMessage, {
        protocol,
        host,
        path,
        id
    }: urlType): string;
    /* The url passed by the server 
    is relative */
    isRelative?: boolean;

    getFileIdFromUrl?(req: http.IncomingMessage): string;
    respectForwardedHeaders?: boolean;


    /*
    Incoming Request is when a incoming request is received.
    Every incoming request with the file id then this function is called
    */
    onIncomingRequest?(req: http.IncomingMessage, res: http.ServerResponse, id: string): void;
}