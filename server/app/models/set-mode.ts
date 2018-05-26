import { Command } from "./command";

export class SetModeCommand extends Command {

    command: 4;
    mode: number;

    build(): string {
        return `4 ${this.mode}`;
    }

    constructor(...cmd: Partial<SetModeCommand>[]) {
        super({ command: 1 }, ...cmd);
    }
}