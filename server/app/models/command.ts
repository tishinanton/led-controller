export abstract class Command {

    command: number;

    abstract build(): string;

    constructor(...cmd: Partial<Command>[]) {
        Object.assign(this, ...cmd);
    }
}