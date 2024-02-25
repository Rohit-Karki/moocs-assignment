import { Upload } from "../Upload";

export interface KVStore<T = Upload> {
    get(key: string): Promise<T | undefined>;
    set(key: string, value: T): void;
    delete(key: string): void;

    list?(): Promise<Array<T | undefined>>;
}