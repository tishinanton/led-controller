export class SetColorCommand {
    command: 1;
    red: number;
    green: number;
    blue: number;

    constructor(...cmd: Partial<SetColorCommand>[]) {
        Object.assign(this, { command: 1 }, ...cmd);
    }
}