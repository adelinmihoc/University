import { Component, OnInit } from '@angular/core';
import {UserService} from '../shared/user.service';

@Component({
  selector: 'app-user-delete',
  templateUrl: './user-delete.component.html',
  styleUrls: ['./user-delete.component.css']
})
export class UserDeleteComponent implements OnInit {

  constructor(private userService: UserService) { }

  ngOnInit(): void {
  }

  // tslint:disable-next-line:typedef
  deleteUser(userId: number) {
    this.userService.deleteUser(userId);
  }

  Number(value: string): number {
    return Number(value);
  }
}
