import { Component, OnInit } from '@angular/core';
import {User} from '../shared/user.model';
import {UserService} from '../shared/user.service';

@Component({
  selector: 'app-user-update',
  templateUrl: './user-update.component.html',
  styleUrls: ['./user-update.component.css']
})
export class UserUpdateComponent implements OnInit {

  constructor(private userService: UserService) { }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  updateUser(id: number, name: string, username: string, password: string, age: number, role: string,
             profile: string, email: string, webpage: string) {
    const user: User = {id, name, username, password, age, role, profile, email, webpage} as User;
    console.log(user);
    this.userService.updateUser(user);

  }

  Number(value: string): number {
    return Number(value);
  }

}
