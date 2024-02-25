import { ServerOptions } from "../../../types";
import { DataStore } from "../../../utils/src/DataStore";
import { BaseHandler } from "./BaseHandler";

// The Client MUST send a POST request against a known upload 
// creation URL to request a new upload resource.
export class PostHandler extends BaseHandler {
    constructor(
        store: DataStore,
        options: ServerOptions
    ) {
        super(options, store);
        this.store = store;
    }
    store: DataStore;

    // Creates a new file for the upload

}