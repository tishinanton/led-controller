import { Command } from "./command";

export class SetColorCommand extends Command {

    command: 1;
    red: number;
    green: number;
    blue: number;

    build(): string {
        return  `1 ${this.red} ${this.green} ${this.blue}`;
    }

    constructor(...cmd: Partial<SetColorCommand>[]) {
        super({ command: 1 }, ...cmd);
    }
}